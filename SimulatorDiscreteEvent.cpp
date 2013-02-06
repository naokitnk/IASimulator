#include "SimulatorDiscreteEvent.h"


SimulatorDiscreteEvent::SimulatorDiscreteEvent(const char* param_filename, bool single_run) : Simulator(param_filename) {
  try {
    this->duration = this->pt.get<int>("parameter_list.duration");
  } catch (std::exception &e) {
    // error
  }
  this->single_run = single_run;

  this->current_time = 0;
  this->prev_capital_authority = 0;
  this->count_ruin = 0;
/*
  double barrier = calculateBarrier();
  authority->setBarrier(barrier);
*/
}


SimulatorDiscreteEvent::~SimulatorDiscreteEvent() {

}


unsigned int SimulatorDiscreteEvent::getDuration() {
  return duration;
}


unsigned int SimulatorDiscreteEvent::getTime() {
  return current_time;
}


void SimulatorDiscreteEvent::generateEventArrive(int j) {
  std::cout << "Generating consumer[" << j << "]'s arrival event..." << std::endl;

  int num_notconsumed_producers = consumers[j]->getNumberOfNotConsumedProducers();
  if (num_notconsumed_producers > 0) {
    //ProfileNormal profile_consumer_arrival_lambda = ProfileNormal(boost::math::normal(0.2, 0.01));
    Profile *profile_consumer_arrival_lambda;
    try {
      profile_consumer_arrival_lambda = new ProfileDouble(this->pt.get<double>("parameter_list.consumer_arrival.lambda"));
    } catch (std::exception &e) {
      try {
        profile_consumer_arrival_lambda = new ProfileNormal(boost::math::normal(this->pt.get<double>("parameter_list.consumer_arrival.lambda_location"), this->pt.get<double>("parameter_list.consumer_arrival.lambda_scale")));
      } catch (std::exception &e) {
        // error
      }
    }
    double arrival_lambda = profile_consumer_arrival_lambda->getSample();
    while (arrival_lambda <= 0) {
      arrival_lambda = profile_consumer_arrival_lambda->getSample();
    }
    delete(profile_consumer_arrival_lambda);

    ProfileExponential profile_consumer_arrival = ProfileExponential(boost::math::exponential(arrival_lambda));
    unsigned int arrival_time = profile_consumer_arrival.getSample() + current_time + 1;

    static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
    boost::uniform_int<int> dist(0, num_notconsumed_producers - 1);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<int> >  sampler(rng, dist);
    int idx = sampler();
    int i = consumers[j]->getIndexOfNotConsumedProducer(idx);
    eventQueue.push((new EventArrive(this, arrival_time, i, j)));
  }
}


void SimulatorDiscreteEvent::addArrivedPair(int i, int j) {
  std::pair<int, int> arrived_index(i, j);
  arrived_indices.push_back(arrived_index);
}


void SimulatorDiscreteEvent::payDividend() {
  if (authority->getCapital() > authority->getBarrier()) {
    double total_dividend = authority->getCapital() - authority->getBarrier();
    double dividend = total_dividend / num_consumer;
    authority->decreaseCapital(total_dividend);
    for (int j = 0; j < num_consumer; j++) {
      consumers[j]->increaseCapital(dividend);
    }
  }
}


void SimulatorDiscreteEvent::fixCost(int i, int j) {
  producers[i]->fixCost(consumers[j], authority);
}


void SimulatorDiscreteEvent::fixValue(int i, int j) {
  consumers[j]->fixValue(producers[i]);
}
 

void SimulatorDiscreteEvent::updateStep() {
  for (int j = 0; j < num_consumer; j++) {
    int current_step = consumers[j]->getStep();
    int count_claim = consumers[j]->getCountClaim();
    int new_step = getNewStep(current_step, count_claim);
    consumers[j]->setStep(new_step);
    consumers[j]->resetCountClaim();
  }
}
 

std::string SimulatorDiscreteEvent::runSimulation() {
  for (unsigned int t = 0; t <= duration; t++) {
    eventQueue.push((new EventNull(this, t)));
    //eventQueue.push((new EventPayDividend(this, t)));
  }

  try {
      int step_update_interval = this->pt.get<int>("parameter_list.step_update_interval");
      for (unsigned int t = step_update_interval + 1; t <= duration; t += step_update_interval) {
        eventQueue.push((new EventUpdateStep(this, t)));
      }
  } catch (std::exception &e) {
    // without Bonus-Malus
  }

  for (int j = 0; j < num_consumer; j++) {
    generateEventArrive(j);
  }

  while (current_time <= duration) {
    if (!eventQueue.empty() && eventQueue.top()->getTime() == current_time) {
      Event *nextEvent = eventQueue.top();
      eventQueue.pop();
      nextEvent->processEvent();
      delete(nextEvent);
    } else {
      if (!arrived_indices.empty()) {      
        handleConsumers();
      }
      if (!eventQueue.empty()) {
        unsigned int next_time = eventQueue.top()->getTime();
        if (next_time > current_time) {
          updateLowestCapital();
          if (single_run) {
            outputCurrentCapitals();
          } else {
            checkRuin();
          }
          current_time = next_time;
        }
      } else {
        updateLowestCapital();
        if (single_run) {
          outputCurrentCapitals();
        } else {
          checkRuin();
        }
        break;
      }
    }
  }

  if (!single_run) {
    outputCurrentCapitals();
  }

  return this->output_stream.str();
}


double SimulatorDiscreteEvent::calculateBarrier() {
  // need to implement
  return 0;
}


void SimulatorDiscreteEvent::updateLowestCapital() {
  double capital = authority->getCapital();
  if (capital < authority->getLowestCapital()) {
    authority->setLowestCapital(capital);
  }
}


void SimulatorDiscreteEvent::outputCurrentCapitals() {
  double lowest_capital_authority = authority->getLowestCapital();
  double capital_authority = authority->getCapital();
  double capital_producers = 0;
  double capital_consumers = 0;
  if (single_run) {
    this->output_stream << current_time << "\t";
  } else {
    this->output_stream << count_ruin << "\t";
    this->output_stream << lowest_capital_authority << "\t";
  }
  this->output_stream << capital_authority << "\t";
  for (int i = 0; i < num_producer; i++) {
    //this->output_stream << producers[i]->getCapital() << "\t";
    capital_producers += producers[i]->getCapital();
  }
  for (int j = 0; j < num_consumer; j++) {
    //this->output_stream << consumers[j]->getCapital() << "\t";
    capital_consumers += consumers[j]->getCapital();
  }
  double capital_all = capital_authority + capital_producers + capital_consumers;
  this->output_stream << capital_producers << "\t" << capital_consumers << "\t" << capital_all << std::endl;
}


void SimulatorDiscreteEvent::checkRuin() {
  double capital_authority = authority->getCapital();
  if (prev_capital_authority >= 0 && capital_authority < 0) {
    count_ruin++;
  }
  prev_capital_authority = capital_authority;
}


void SimulatorDiscreteEvent::handleConsumers() {
  // initiate transactions
  int num_tx_occurred = 0;
  for (std::vector<std::pair<int, int> >::iterator itr = arrived_indices.begin(); itr != arrived_indices.end(); ++itr) {
    int i = (*itr).first;
    int j = (*itr).second;

    if (consumers[j]->obtainInformation(authority, producers[i])) {
      std::cout << "transaction occurred between producer[" << i << "] and consumer[" << j << "]" << std::endl;
      num_tx_occurred++;
      consumers[j]->consumed(i);

      // generate fix cost event
///*
      //ProfileNormal profile_cost_arrival_lambda = ProfileNormal(boost::math::normal(0.5, 0.01));
      Profile *profile_cost_arrival_lambda;
      try {
        profile_cost_arrival_lambda = new ProfileDouble(this->pt.get<double>("parameter_list.cost_arrival.lambda"));
      } catch (std::exception &e) {
        try {
          profile_cost_arrival_lambda = new ProfileNormal(boost::math::normal(this->pt.get<double>("parameter_list.cost_arrival.lambda_location"), this->pt.get<double>("parameter_list.cost_arrival.lambda_scale")));
        } catch (std::exception &e) {
          // error
        }
      }
      double cost_arrival_lambda = profile_cost_arrival_lambda->getSample();
      while (cost_arrival_lambda <= 0) {
        cost_arrival_lambda = profile_cost_arrival_lambda->getSample();
      }
      delete(profile_cost_arrival_lambda);

      ProfileExponential profile_cost_arrival = ProfileExponential(boost::math::exponential(cost_arrival_lambda));
      unsigned int cost_arrival_time = profile_cost_arrival.getSample() + current_time + 1;
      eventQueue.push((new EventFixCost(this, cost_arrival_time, i, j)));
//*/
/*
      ProfileUniform profile_uniform = ProfileUniform(boost::math::uniform(0, 1.0));
      double random_probability = profile_uniform.getSample();
      if (random_probability <= consumers[j]->getClaimProbability()) {
        //ProfileNormal profile_cost_arrival_lambda = ProfileNormal(boost::math::normal(0.5, 0.01));
        Profile *profile_cost_arrival_lambda;
        try {
          profile_cost_arrival_lambda = new ProfileDouble(this->pt.get<double>("parameter_list.cost_arrival.lambda"));
        } catch (std::exception &e) {
          try {
            profile_cost_arrival_lambda = new ProfileNormal(boost::math::normal(this->pt.get<double>("parameter_list.cost_arrival.lambda_location"), this->pt.get<double>("parameter_list.cost_arrival.lambda_scale")));
          } catch (std::exception &e) {
            // error
          }
        }
        double cost_arrival_lambda = profile_cost_arrival_lambda->getSample();
        while (cost_arrival_lambda <= 0) {
          cost_arrival_lambda = profile_cost_arrival_lambda->getSample();
        }
        delete(profile_cost_arrival_lambda);

        ProfileExponential profile_cost_arrival = ProfileExponential(boost::math::exponential(cost_arrival_lambda));
        unsigned int cost_arrival_time = profile_cost_arrival.getSample() + current_time + 1;
        eventQueue.push((new EventFixCost(this, cost_arrival_time, i, j)));
      }
*/

      // generate fix value event
      //ProfileNormal profile_value_arrival_lambda = ProfileNormal(boost::math::normal(1.0, 0.01));
      Profile *profile_value_arrival_lambda;
      try {
        profile_value_arrival_lambda = new ProfileDouble(this->pt.get<double>("parameter_list.value_arrival.lambda"));
      } catch (std::exception &e) {
        try {
          profile_value_arrival_lambda = new ProfileNormal(boost::math::normal(this->pt.get<double>("parameter_list.value_arrival.lambda_location"), this->pt.get<double>("parameter_list.value_arrival.lambda_scale")));
        } catch (std::exception &e) {
          // error
        }
      }
      double value_arrival_lambda = profile_value_arrival_lambda->getSample();
      while (value_arrival_lambda <= 0) {
        value_arrival_lambda = profile_value_arrival_lambda->getSample();
      }
      delete(profile_value_arrival_lambda);

      ProfileExponential profile_value_arrival = ProfileExponential(boost::math::exponential(value_arrival_lambda));
      unsigned int value_arrival_time = profile_value_arrival.getSample() + current_time + 1;
      eventQueue.push((new EventFixValue(this, value_arrival_time, i, j)));
    }
  }
  if (num_tx_occurred > 0) {
    std::cout << num_tx_occurred << " transaction(s) occurred at time " << current_time << std::endl;
  }


  // generate next arrival events
  if (getDuration() > current_time) {
    for (std::vector<std::pair<int, int> >::iterator itr = arrived_indices.begin(); itr != arrived_indices.end(); ++itr) {
      generateEventArrive((*itr).second);
    }
  }
  arrived_indices.clear();
}


int SimulatorDiscreteEvent::getNewStep(int current_step, int count_claim) {
  assert(1 <= current_step && current_step <= 14);
  assert(count_claim >= 0);

  int new_step;

  switch (count_claim) {
    case 0:
      switch (current_step) {
        case 1:
          new_step = 2;
          break;
        case 2:
          new_step = 3;
          break;
        case 3:
          new_step = 4;
          break;
        case 4:
          new_step = 5;
          break;
        case 5:
          new_step = 6;
          break;
        case 6:
          new_step = 7;
          break;
        case 7:
          new_step = 8;
          break;
        case 8:
          new_step = 9;
          break;
        case 9:
          new_step = 10;
          break;
        case 10:
          new_step = 11;
          break;
        case 11:
          new_step = 12;
          break;
        case 12:
          new_step = 13;
          break;
        default:
          new_step = 14;
          break;
      }
      break; 
    case 1:
      switch (current_step) {
        case 14:
          new_step = 9;
          break;
        case 13:
        case 12:
          new_step = 8;
          break;
        case 11:
        case 10:
          new_step = 7;
          break;
        case 9:
          new_step = 6;
          break;
        case 8:
          new_step = 5;
          break;
        case 7:
          new_step = 4;
          break;
        case 6:
          new_step = 3;
          break;
        case 5:
          new_step = 2;
          break;
        default:
          new_step = 1;
          break;
      }
      break; 
    case 2:
      switch (current_step) {
        case 14:
          new_step = 5;
          break;
        case 13:
        case 12:
          new_step = 4;
          break;
        case 11:
        case 10:
          new_step = 3;
          break;
        case 9:
          new_step = 2;
          break;
        default:
          new_step = 1;
          break;
      }
      break; 
    default:
      new_step = 1;
      break; 
  }

  return new_step;
}


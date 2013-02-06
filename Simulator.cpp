#include "Simulator.h"


Simulator::Simulator(const char* param_filename) {
  read_xml(param_filename, this->pt);

  try {
    this->num_producer = this->pt.get<int>("parameter_list.global.num_producer");
    this->num_consumer = this->pt.get<int>("parameter_list.global.num_consumer");
  } catch (std::exception &e) {
    // error
  }
  this->authority = new Authority(this);
  try {
    authority->setFeeRate(this->pt.get<double>("parameter_list.global.fee_rate"));
  } catch (std::exception &e) {
    // no fee
  }
  for (int i = 0; i < this->num_producer; i++) {
    Producer *p = new Producer(this, i);
    this->producers.push_back(p);
  }
  for (int j = 0; j < this->num_consumer; j++) {
    //Consumer *c = new Consumer(this, j);
    double claim_prob = 1.0 * (j+1) / this->num_consumer;
    Consumer *c = new Consumer(this, j, claim_prob);
    this->consumers.push_back(c);
  }

  setParameters();
}


Simulator::~Simulator() {
  delete(authority);
  for (int i = 0; i < num_producer; i++) {
    producers[i]->deleteCosts();
  }
  for (int j = 0; j < num_consumer; j++) {
    consumers[j]->deleteValues();
  }
  for (int i = 0; i < num_producer; i++) {
    delete(producers[i]);
  }
  for (int j = 0; j < num_consumer; j++) {
    delete(consumers[j]);
  }
}


int Simulator::getNumberOfProducers() {
  return num_producer;
}


int Simulator::getNumberOfConsumers() {
  return num_consumer;
}


void Simulator::setParameters() {
  // Alpha Profile
  Profile *alpha_profile_authority, *alpha_profile_consumer;
  try {
    alpha_profile_authority = new ProfileDouble(this->pt.get<double>("parameter_list.alpha.authority"));
  } catch (std::exception &e) {
    try {
      alpha_profile_authority = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.alpha.authority_min"), this->pt.get<double>("parameter_list.alpha.authority_max")));
    } catch (std::exception &e) {
      // error
    }  
  }
  try {
    alpha_profile_consumer = new ProfileDouble(this->pt.get<double>("parameter_list.alpha.consumer"));
  } catch (std::exception &e) {
    try {
      alpha_profile_consumer = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.alpha.consumer_min"), this->pt.get<double>("parameter_list.alpha.consumer_max")));
    } catch (std::exception &e) {
      // error
    }  
  }

  // Capital Profile
  Profile *capital_profile_authority, *capital_profile_producer, *capital_profile_consumer;
  try {
    capital_profile_authority = new ProfileDouble(this->pt.get<double>("parameter_list.capital.authority"));
  } catch (std::exception &e) {
    try {
      capital_profile_authority = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.capital.authority_min"), this->pt.get<double>("parameter_list.capital.authority_max")));
    } catch (std::exception &e) {
      // error
    }  
  }
  try {
    capital_profile_producer = new ProfileDouble(this->pt.get<double>("parameter_list.capital.producer"));
  } catch (std::exception &e) {
    try {
      capital_profile_producer = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.capital.producer_min"), this->pt.get<double>("parameter_list.capital.producer_max")));
    } catch (std::exception &e) {
      // error
    }  
  }
  try {
    capital_profile_consumer = new ProfileDouble(this->pt.get<double>("parameter_list.capital.consumer"));
  } catch (std::exception &e) {
    try {
      capital_profile_consumer = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.capital.consumer_min"), this->pt.get<double>("parameter_list.capital.consumer_max")));
    } catch (std::exception &e) {
      // error
    }  
  }

  // Cost Profile
  Profile *cost_location, *cost_scale, *cost_shape, *cost_lambda, *cost_claimprob;
  std::string cost_profile;
  try {
    cost_profile = this->pt.get<std::string>("parameter_list.cost.<xmlattr>.profile");
  } catch (std::exception &e) {
    // error
  }
  if (cost_profile == "Normal") {
    try {
      cost_location = new ProfileDouble(this->pt.get<double>("parameter_list.cost.location"));
    } catch (std::exception &e) {
      try {
        cost_location = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.location_min"), this->pt.get<double>("parameter_list.cost.location_max")));
      } catch (std::exception &e) {
        // error
      }
    }
    try {
      cost_scale = new ProfileDouble(this->pt.get<double>("parameter_list.cost.scale"));
    } catch (std::exception &e) {
      try {
        cost_scale = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.scale_min"), this->pt.get<double>("parameter_list.cost.scale_max")));
      } catch (std::exception &e) {
        // error
      }
    }
  } else if (cost_profile == "Exponential") {
    try {
      cost_lambda = new ProfileDouble(this->pt.get<double>("parameter_list.cost.lamda"));
    } catch (std::exception &e) {
      try {
        cost_lambda = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.lambda_min"), this->pt.get<double>("parameter_list.cost.lambda_max")));
      } catch (std::exception &e) {
        // error
      }
    }
  } else if (cost_profile == "ZAGA") {
    try {
      cost_claimprob = new ProfileDouble(this->pt.get<double>("parameter_list.cost.claimprob"));
    } catch (std::exception &e) {
      try {
        cost_claimprob = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.claimprob_min"), this->pt.get<double>("parameter_list.cost.claimprob_max")));
      } catch (std::exception &e) {
        // error
      }
    }
    try {
      cost_shape = new ProfileDouble(this->pt.get<double>("parameter_list.cost.shape"));
    } catch (std::exception &e) {
      try {
        cost_shape = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.shape_min"), this->pt.get<double>("parameter_list.cost.shape_max")));
      } catch (std::exception &e) {
        // error
      }
    }
    try {
      cost_scale = new ProfileDouble(this->pt.get<double>("parameter_list.cost.scale"));
    } catch (std::exception &e) {
      try {
        cost_scale = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.cost.scale_min"), this->pt.get<double>("parameter_list.cost.scale_max")));
      } catch (std::exception &e) {
        // error
      }
    }
  } else {
    // error (unsupported cost profile)
  }

  // Value Profile
  Profile *value_location, *value_scale;
  std::string value_profile;
  try {
    value_profile = this->pt.get<std::string>("parameter_list.value.<xmlattr>.profile");
  } catch (std::exception &e) {
    // error
  }
  if (value_profile == "Normal") {
    try {
      value_location = new ProfileDouble(this->pt.get<double>("parameter_list.value.location"));
    } catch (std::exception &e) {
      try {
        value_location = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.value.location_min"), this->pt.get<double>("parameter_list.value.location_max")));
      } catch (std::exception &e) {
        // error
      }
    }
    try {
      value_scale = new ProfileDouble(this->pt.get<double>("parameter_list.value.scale"));
    } catch (std::exception &e) {
      try {
        value_scale = new ProfileUniform(boost::math::uniform(this->pt.get<double>("parameter_list.value.scale_min"), this->pt.get<double>("parameter_list.value.scale_max")));
      } catch (std::exception &e) {
        // error
      }
    }
  } else {
    // error (unsupported value profile)
  }


  // Set Parameters
  authority->setUtilityExponential(alpha_profile_authority->getSample());
  authority->setCapital(capital_profile_authority->getSample());
  authority->setLowestCapital(authority->getCapital());
  for (int j = 0; j < num_consumer; j++) {
    consumers[j]->setUtilityExponential(alpha_profile_consumer->getSample());
    consumers[j]->setCapital(capital_profile_consumer->getSample());
  }

  for (int i = 0; i < num_producer; i++) {
    producers[i]->setCapital(capital_profile_producer->getSample());
    for (int j = 0; j < num_consumer; j++) {
      Profile *cost;
      if (cost_profile == "Normal") {
        cost = new ProfileNormal(boost::math::normal(cost_location->getSample(), cost_scale->getSample()));
      } else if (cost_profile == "Exponential") {
        cost = new ProfileExponential(boost::math::exponential(cost_lambda->getSample()));
      } else if (cost_profile == "ZAGA") {
        cost = new ProfileZAGA(boost::math::gamma_distribution<double>(cost_shape->getSample(), cost_scale->getSample()), cost_claimprob->getSample());
        //cost = new ProfileZAGA(boost::math::gamma_distribution<double>(cost_shape->getSample(), cost_scale->getSample()), consumers[j]->getClaimProbability());
      } else {
        // error (unsupported cost profile)
      }
      producers[i]->setCost(consumers[j], cost);

      Profile *value;
      if (value_profile == "Normal") {
        value = new ProfileNormal(boost::math::normal(value_location->getSample(), value_scale->getSample()));
      } else {
        // error (unsupported value profile)
      }
      consumers[j]->setValue(producers[i], value);
    }
  }


  // delete
  delete(alpha_profile_authority);
  delete(alpha_profile_consumer);
  delete(capital_profile_authority);
  delete(capital_profile_producer);
  delete(capital_profile_consumer);
  if (cost_profile == "Normal") {
    delete(cost_location);
    delete(cost_scale);
  } else if (cost_profile == "Exponential") {
    delete(cost_lambda);
  } else if (cost_profile == "ZAGA") {
    delete(cost_claimprob);
    delete(cost_shape);
    delete(cost_scale);
  } else {
    // error (unsupported cost profile)
  }
  if (value_profile == "Normal") {
    delete(value_location);
    delete(value_scale);
  } else {
    // error (unsupported value profile)
  }
}


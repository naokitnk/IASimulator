#include "SimulatorOneRound.h"


SimulatorOneRound::SimulatorOneRound(const char* param_filename) : Simulator(param_filename) {

}


SimulatorOneRound::~SimulatorOneRound() {

}


std::string SimulatorOneRound::runSimulation() {
  double init_capital_authority, end_capital_authority;
  init_capital_authority = authority->getCapital();
  end_capital_authority = init_capital_authority;

  static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
  boost::uniform_int<int> dist(0, num_producer - 1);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<int> >  sampler(rng, dist);
  for (int j = 0; j < num_consumer; j++) {
    int i = sampler();
    consumers[j]->addCandidate(producers[i]);
  }

  double init_capital_producer[num_producer], end_capital_producer[num_producer];
  for (int i = 0; i < num_producer; i++) {
    init_capital_producer[i] = producers[i]->getCapital();
    end_capital_producer[i] = init_capital_producer[i];
  }

  double init_capital_consumer[num_consumer], end_capital_consumer[num_consumer];
  for (int j = 0; j < num_consumer; j++) {
    init_capital_consumer[j] = consumers[j]->getCapital();
    end_capital_consumer[j] = init_capital_consumer[j];
  }


  // initiate transactions
  bool tx_occurred[num_producer][num_consumer];
  for (int j = 0; j < num_consumer; j++) {
    std::vector<Producer *> candidates = consumers[j]->getCandidates();
    for (int i = 0; i < num_producer; i++) {
      std::vector<Producer *>::iterator itr = find(candidates.begin(), candidates.end(), producers[i]);
      if (itr == candidates.end()) {
	tx_occurred[i][j] = false;
      } else {
	tx_occurred[i][j] = consumers[j]->obtainInformation(authority, producers[i]);
      }
    }
  }



  // fix costs and values
  int num_tx_occurred = 0;
  for (int i = 0; i < num_producer; i++) {
    for (int j = 0; j < num_consumer; j++) {
      if (tx_occurred[i][j]) {
	std::cout << "transaction occurred between producer[" << i << "] and consumer[" << j << "]" << std::endl;
	producers[i]->fixCost(consumers[j], authority);
	consumers[j]->fixValue(producers[i]);
	num_tx_occurred++;
      }
    }
  }
  for (int i = 0; i < num_producer; i++) {
    end_capital_producer[i] = producers[i]->getCapital();
  }
  for (int j = 0; j < num_consumer; j++) {
    end_capital_consumer[j] = consumers[j]->getCapital();
  }
  end_capital_authority = authority->getCapital();


  // output results
  std::cout << num_tx_occurred << " transaction(s) occurred" << std::endl;
  //std::cout << "init_capital_authority = " << init_capital_authority << std::endl;
  //std::cout << "end_capital_authority = " << end_capital_authority << std::endl;
  double profit_authority = end_capital_authority - init_capital_authority;
  std::cout << "profit_authority = " << profit_authority << std::endl;
  double sum_producer_profit = 0;
  for (int i = 0; i < num_producer; i++) {
    //std::cout << "init_capital_producer[" << i << "] = " << init_capital_producer[i] << std::endl;
    //std::cout << "end_capital_producer[" << i << "] = " << end_capital_producer[i] << std::endl;
    double profit = end_capital_producer[i] - init_capital_producer[i];
    sum_producer_profit += profit;
    std::cout << "profit_producer[" << i << "] = " << profit << std::endl;
  }
  double sum_consumer_profit = 0;
  for (int j = 0; j < num_consumer; j++) {
    //std::cout << "init_capital_consumer[" << j << "] = " << init_capital_consumer[j] << std::endl;
    //std::cout << "end_capital_consumer[" << j << "] = " << end_capital_consumer[j] << std::endl;
    double profit = end_capital_consumer[j] - init_capital_consumer[j];
    sum_consumer_profit += profit;
    std::cout << "profit_consumer[" << j << "] = " << profit << std::endl;
  }
  double sum_all_profit = profit_authority + sum_producer_profit + sum_consumer_profit;
  this->output_stream << num_tx_occurred << "\t" << profit_authority << "\t" << sum_producer_profit << "\t" << sum_consumer_profit << "\t" << sum_all_profit << std::endl;


  return this->output_stream.str();
}


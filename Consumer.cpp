#include "Simulator.h"
#include "Principal.h"
#include "Authority.h"
#include "Producer.h"
#include "Consumer.h"
#include "Profile.h"


Consumer::Consumer(Simulator *sim, int id, double claim_prob) : Principal(sim) {
  this->id = id;
  this->step = 2;
  this->count_claim = 0;
  this->claim_prob = claim_prob;
  int num_producer = simulator->getNumberOfProducers();
  for (int i = 0; i < num_producer; i++) {
    not_consumed_indices.push_back(i);
  }
}


void Consumer::deleteValues() {
  for (std::map<Producer *, Profile *>::iterator itr = values.begin(); itr != values.end(); ++itr) {
    delete((*itr).second);
  }
}


int Consumer::getID() {
  return this->id;
}


void Consumer::setStep(int step) {
  assert(1 <= step && step <= 14);
  this->step = step;
}


int Consumer::getStep() {
  return this->step;
}


void Consumer::resetCountClaim() {
  this->count_claim = 0;
}


void Consumer::incrementCountClaim() {
  this->count_claim++;
}


int Consumer::getCountClaim() {
  return this->count_claim;
}


void Consumer::setClaimProbability(double claim_prob) {
  this->claim_prob = claim_prob;
}


double Consumer::getClaimProbability() {
  return this->claim_prob;
}


void Consumer::setPolicy(Producer *producer) {
  policies[producer] = true;
}


bool Consumer::havePolicy(Producer *producer) {
  std::map<Producer *, bool>::iterator it = policies.find(producer);
  if (it != policies.end() && (*it).second) {
    return true;
  } else {
    return false;
  }
}


void Consumer::setValue(Producer *producer, Profile *value) {
  values[producer] = value;
}


Profile* Consumer::getValue(Producer *producer) {
  return values[producer];
}


bool Consumer::addCandidate(Producer *producer) {
  std::vector<Producer *>::iterator itr = find(candidates.begin(), candidates.end(), producer);
  if (itr == candidates.end()) {
    candidates.push_back(producer);
    return true;
  } else {
    return false;
  }
}


std::vector<Producer *> Consumer::getCandidates() {
  return candidates;
}


double Consumer::getMaximumPremium(Producer *producer) {
  return calculateMaximumPremiumExponential(producer);
}


bool Consumer::obtainInformation(Authority *authority, Producer *producer) {
  double premium = authority->getPremium(producer, this);
  if (premium > this->capital || premium > getMaximumPremium(producer)) {
    return false;
  }

/*
  int num_sample = 10000;
  double expected_utility = 0;
  for (int i = 0; i < num_sample; i++) {
    expected_utility += getUtility(values[producer]->getSample() - premium);
  }
  expected_utility /= num_sample;
  double current_utility = getUtility();
  if (expected_utility < current_utility) {  // E[u(w+Y-premium)] < u(w)
    return false;
  }
*/

  /*
  std::cout << "premium = " << premium << std::endl;
  std::cout << "expected_value = " << values[producer]->getMean() << std::endl;
  std::cout << "capital = " << this->capital << std::endl;
  */

  bool obtained = false;
  if (authority->sellPolicy(producer, this)) {
    obtained = producer->shareInformation(this);
  }
  return obtained;
}


void Consumer::fixValue(Producer *producer) {
  double value = values[producer]->getSample();
/*
  for (int i = 1; i < 10000; i++) {
    double tmp = values[producer]->getSample();
    if (tmp < value) {
      value = tmp;
    }
  }
*/
  if (value < 0) {
    value = 0;
  }
  ///*
  std::cout << "expected value = " << values[producer]->getMean() << std::endl;
  std::cout << "actual value = " << value << std::endl;
  //*/
  this->capital += value;
}


int Consumer::getNumberOfNotConsumedProducers() {
  return (int) not_consumed_indices.size();
}


int Consumer::getIndexOfNotConsumedProducer(int idx) {
  return not_consumed_indices[idx]; 
}


void Consumer::consumed(int i) {
  std::vector<int>::iterator itr = find(not_consumed_indices.begin(), not_consumed_indices.end(), i);
  if (itr != not_consumed_indices.end()) {
    not_consumed_indices.erase(itr);
  } else {
    std::cerr << "trying to erase nonexistent element" << std::endl;
    exit(EXIT_FAILURE);         // should use exception
  }

}


double Consumer::calculateMaximumPremiumExponential(Producer *producer) {
  return values[producer]->getExponentialPremium(-1 * ((UtilityExponential *) this->utility_function)->getAlpha());
}


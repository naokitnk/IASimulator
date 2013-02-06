#ifndef CONSUMER_H_
#define CONSUMER_H_

#include <map>
#include <vector>
#include <iostream>
#include <boost/math/distributions.hpp>

#include "Principal.h"


class Simulator;
class Authority;
class Producer;
class Profile;


class Consumer : public Principal {
 public:
  Consumer(Simulator *sim, int id, double claim_prob = 1.0);
  void deleteValues();
  int getID();
  void setStep(int step);
  int getStep();
  void resetCountClaim();
  void incrementCountClaim();
  int getCountClaim();
  void setClaimProbability(double claim_prob);
  double getClaimProbability();
  void setPolicy(Producer *producer);
  bool havePolicy(Producer *producer);
  void setValue(Producer *producer, Profile *value);
  Profile* getValue(Producer *producer);
  bool addCandidate(Producer *producer);
  std::vector<Producer *> getCandidates();
  double getMaximumPremium(Producer *producer);
  bool obtainInformation(Authority *authority, Producer *producer);
  void fixValue(Producer *producer);
  int getNumberOfNotConsumedProducers();
  int getIndexOfNotConsumedProducer(int idx);
  void consumed(int i);


 private:
  int id, step, count_claim;
  double claim_prob;
  std::map<Producer *, Profile *> values;
  std::vector<Producer *> candidates;
  std::map<Producer *, bool> policies;
  std::vector<int> not_consumed_indices;

  double calculateMaximumPremiumExponential(Producer *producer);
};
#endif

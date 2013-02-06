#ifndef AUTHORITY_H_
#define AUTHORITY_H_

#include <limits>
#include <vector>

#include "Principal.h"


class Simulator;
class Producer;
class Consumer;
class Profile;


class Authority : public Principal {
 public:
  Authority(Simulator *sim, double fee_rate = 0);
  Authority(Simulator *sim, double capital, double fee_rate = 0);
  //Authority(Simulator *sim, double capital, double barrier = std::numeric_limits<double>::max());
  void setLowestCapital(double lowestCapital);
  double getLowestCapital();
  void setFeeRate(double fee_rate);
  double getFeeRate();
  void setBarrier(double barrier);
  double getBarrier();
  double getPremium(Producer *producer, Consumer *consumer);
  bool sellPolicy(Producer *producer, Consumer *consumer);


 private:
  double lowestCapital;
  double fee_rate;
  double barrier;

  double getPremium(Producer *producer, Consumer *consumer, double rate);
  double calculatePremiumExponential(Producer *producer, Consumer *consumer);
  double getWeight(int step);
};
#endif

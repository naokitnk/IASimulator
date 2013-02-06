#ifndef PRODUCER_H_
#define PRODUCER_H_

#include <map>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>

#include "Principal.h"


class Simualtor;
class Authority;
class Consumer;
class Profile;


class Producer : public Principal {
 public:
  Producer(Simulator *sim, int id);
  void deleteCosts();
  int getID();
  void setCost(Consumer *consumer, Profile *cost);
  Profile* getCost(Consumer *consumer);
  bool shareInformation(Consumer *consuemer);
  void fixCost(Consumer *consumer, Authority *authority);


 private:
  int id;
  std::map<Consumer *, Profile *> costs;
};
#endif

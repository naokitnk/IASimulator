#include "Principal.h"
#include "Authority.h"
#include "Producer.h"
#include "Consumer.h"
#include "Profile.h"


Producer::Producer(Simulator *sim, int id) : Principal(sim) {
  this->id = id;
}


void Producer::deleteCosts() {
  for (std::map<Consumer *, Profile *>::iterator itr = costs.begin(); itr != costs.end(); ++itr) {
    delete((*itr).second); 
  }
}


int Producer::getID() {
  return this->id;
}


void Producer::setCost(Consumer *consumer, Profile *cost) {
  costs[consumer] = cost;
}


Profile* Producer::getCost(Consumer *consumer) {
  return costs[consumer];
}


bool Producer::shareInformation(Consumer *consumer) {
  if (consumer->havePolicy(this)) {
    return true;
  } else {
    return false;
  }
}


void Producer::fixCost(Consumer *consumer, Authority *authority) {
  double cost = costs[consumer]->getSample();
/*
  for (int i = 1; i < 10000; i++) {
    double tmp = costs[consumer]->getSample();
    if (tmp > cost) {
      cost = tmp;
    }
  }
*/
  if (cost < 0) {
    cost = 0;
  }
  ///*
  std::cout << "expected cost = " << costs[consumer]->getMean() << std::endl;
  std::cout << "actual cost = " << cost << std::endl;
  //*/
  if (cost > 0) {
    consumer->incrementCountClaim();
    authority->decreaseCapital(cost);
  }
}


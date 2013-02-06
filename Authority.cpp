#include "Principal.h"
#include "Authority.h"
#include "Producer.h"
#include "Consumer.h"


Authority::Authority(Simulator *sim, double fee_rate) : Principal(sim) {
  this->fee_rate = fee_rate;
}


Authority::Authority(Simulator *sim, double capital, double fee_rate) : Principal(sim, capital) {
  this->lowestCapital = capital;
  this->fee_rate = fee_rate;
}


/*
Authority::Authority(Simulator *sim, double capital, double barrier) : Principal(sim, capital) {
  this->lowestCapital = capital;
  this->barrier = barrier;
}
*/


void Authority::setLowestCapital(double lowestCapital) {
  this->lowestCapital = lowestCapital;
}


double Authority::getLowestCapital() {
  return lowestCapital;
}


void Authority::setFeeRate(double fee_rate) {
  this->fee_rate = fee_rate;
}


double Authority::getFeeRate() {
  return fee_rate;
}


void Authority::setBarrier(double barrier) {
  this->barrier = barrier;
}


double Authority::getBarrier() {
  return barrier;
}


double Authority::getPremium(Producer *producer, Consumer *consumer) {
  return getPremium(producer, consumer, fee_rate);
}


bool Authority::sellPolicy(Producer *producer, Consumer *consumer) {
  double premium = getPremium(producer, consumer);
  double genuine_premium = getPremium(producer, consumer, 0);
  double fee = premium - genuine_premium;
  if (consumer->getCapital() < premium) {
    return false;
  }

/*
  int num_sample = 10000;
  double expected_utility = 0;
  for (int i = 0; i < num_sample; i++) {
    expected_utility += getUtility(premium - producer->getCost(consumer)->getSample());
  }
  expected_utility /= num_sample;
  double current_utility = getUtility();
  if (expected_utility < current_utility) {  // E[u(w+premium-X)] < u(w)
std::cout << "smaller utility" << std::endl;
    return false;
  }
*/

  consumer->decreaseCapital(premium);
  this->increaseCapital(genuine_premium);
  producer->increaseCapital(fee);
  consumer->setPolicy(producer);
std::cout << "premium for policy between producer[" << producer->getID() << "] and consumer[" << consumer->getID() << "]: " << premium << std::endl;
  return true;
}


double Authority::getPremium(Producer *producer, Consumer *consumer, double rate) {
  double premium = calculatePremiumExponential(producer, consumer);

/*
  double consumer_capital = consumer->getCapital();
  if (consumer_capital >= premium) {
    double maximumPremium = consumer->getMaximumPremium(producer);
    if (maximumPremium > premium) {
      //maximumPremium = (premium + maximumPremium) / 2;
      if (maximumPremium <= consumer_capital) {
        premium = maximumPremium;
      } else {
        premium = consumer_capital;
      }
    }
  }
*/

  //premium *= getWeight(consumer->getStep());
  return premium * (1 + rate);
}


double Authority::calculatePremiumExponential(Producer *producer, Consumer *consumer) {
  return producer->getCost(consumer)->getExponentialPremium(((UtilityExponential *) this->utility_function)->getAlpha());
}


double Authority::getWeight(int step) {
  assert(1 <= step && step <= 14);
  switch (step) {
    case 1: return 1.2;
    case 2: return 1.0;
    case 3: return 0.9;
    case 4: return 0.8;
    case 5: return 0.7;
    case 6: return 0.6;
    case 7: return 0.55;
    case 8: return 0.5;
    case 9: return 0.45;
    case 10: return 0.4;
    case 11: return 0.375;
    case 12: return 0.35;
    case 13: return 0.325;
    case 14: return 0.3;
    default: return 1.0;
  }
}


#include "Utility.h"
#include "UtilityPower.h"


UtilityPower::UtilityPower(double c) : Utility() {
  assert(0 < c && c <= 1);
  this->c = c;
}


double UtilityPower::getUtility(double x) {
  assert(x > 0);
  return pow(x, this->c);
}


double UtilityPower::getRiskAversionCoefficient(double x) {
  assert(x > 0);
  return (1 - this->c) / x;
}


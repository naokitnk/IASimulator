#include "Utility.h"
#include "UtilityQuadratic.h"


UtilityQuadratic::UtilityQuadratic(double c) : Utility() {
  assert(c > 0);
  this->c = c;
}


double UtilityQuadratic::getC() {
  return this->c;
}


double UtilityQuadratic::getUtility(double x) {
  assert(x <= this->c);
  return x - pow(x, 2) / (2 * this->c);
}


double UtilityQuadratic::getRiskAversionCoefficient(double x) {
  assert(x <= this->c);
  return 1 / (this->c - x);
}


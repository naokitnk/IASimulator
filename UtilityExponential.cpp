#include "Utility.h"
#include "UtilityExponential.h"


UtilityExponential::UtilityExponential(double alpha) : Utility() {
  assert(alpha > 0);
  this->alpha = alpha;
}


double UtilityExponential::getAlpha() {
  return this->alpha;
}


double UtilityExponential::getUtility(double x) {
  return 1 - exp(-(this->alpha) * x);
  //return (1 - exp(-(this->alpha) * x)) / this->alpha;
}

double UtilityExponential::getRiskAversionCoefficient(double x) {
  return this->alpha;
}

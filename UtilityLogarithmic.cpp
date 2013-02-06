#include "Utility.h"
#include "UtilityLogarithmic.h"


//UtilityLogarithmic::UtilityLogarithmic(double alpha) : Utility() {
UtilityLogarithmic::UtilityLogarithmic() : Utility() {
  //this->alpha = alpha;
}


double UtilityLogarithmic::getUtility(double x) {
  //assert(x > -(this->alpha));
  assert(x > 0);
  //return log(this->alpha + x);
  return log(x);
}


double UtilityLogarithmic::getRiskAversionCoefficient(double x) {
  //assert(x > -(this->alpha));
  assert(x > 0);
  return 1/x;
}


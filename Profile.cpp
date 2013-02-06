#include "Profile.h"


Profile::Profile() {
}


Profile::~Profile() {
}


double Profile::getNetPremium() {
  return getMean();
}


double Profile::getExpectedValuePremium(double theta) {
  return (1 + theta) * getMean();
}


double Profile::getVariancePremium(double alpha) {
  return getMean() + alpha * getVariance();
}


double Profile::getStandardDeviationPremium(double beta) {
  return getMean() + beta * sqrt(getVariance());
}


double Profile::getExponentialPremium(double alpha) {
  double mgf = getMGF(alpha);
  assert(mgf > 0);
  return log(mgf) / alpha;
}


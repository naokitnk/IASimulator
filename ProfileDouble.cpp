#include "Profile.h"
#include "ProfileDouble.h"


ProfileDouble::ProfileDouble(double profile) : Profile() {
  this->profile = profile;
}


double ProfileDouble::getMean() {
  return profile;
}


double ProfileDouble::getVariance() {
  return 0;
}


double ProfileDouble::getPDF(double x) {
  assert(x >= 0);
  if (x == profile) {
    return 1;
  } else {
   return 0;
  }
}


double ProfileDouble::getCDF(double x) {
  assert(x >= 0);
  if (x >= profile) {
    return 1;
  } else {
    return 0;
  }
}


double ProfileDouble::getQuantile(double p) {
  return profile;
}


double ProfileDouble::getMGF(double t) {
  return 1 + t * profile;
}


double ProfileDouble::getSample() {
  return profile;
}


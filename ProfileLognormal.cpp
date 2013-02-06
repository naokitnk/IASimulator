#include "Profile.h"
#include "ProfileLognormal.h"


ProfileLognormal::ProfileLognormal(boost::math::lognormal profile) : Profile() {
  this->profile = profile;
}


double ProfileLognormal::getMean() {
  return boost::math::mean(profile);
}


double ProfileLognormal::getVariance() {
  return boost::math::variance(profile);
}


double ProfileLognormal::getPDF(double x) {
  return boost::math::pdf(profile, x);
}


double ProfileLognormal::getCDF(double x) {
  return boost::math::cdf(profile, x);
}


double ProfileLognormal::getQuantile(double p) {
  return boost::math::quantile(profile, p);
}


double ProfileLognormal::getMGF(double t) {
  // MGF is not defined for Lognormal Distribution
  return 0;
}


double ProfileLognormal::getSample() {
  // Create a Mersenne twister random number generator
  // that is seeded once with #seconds since 1970
  static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
 
  // select Lognormal probability distribution
  boost::lognormal_distribution<double> dist(boost::math::mean(profile), sqrt(boost::math::variance(profile)));
 
  // bind random number generator to distribution, forming a function
  boost::variate_generator<boost::mt19937&, boost::lognormal_distribution<double> >  sampler(rng, dist);
  
  // sample from the distribution
  return sampler();
}


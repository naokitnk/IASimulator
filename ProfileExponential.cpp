#include "Profile.h"
#include "ProfileExponential.h"


ProfileExponential::ProfileExponential(boost::math::exponential profile) : Profile() {
  this->profile = profile;
}


double ProfileExponential::getMean() {
  return boost::math::mean(profile);
}


double ProfileExponential::getVariance() {
  return boost::math::variance(profile);
}


double ProfileExponential::getPDF(double x) {
  return boost::math::pdf(profile, x);
}


double ProfileExponential::getCDF(double x) {
  return boost::math::cdf(profile, x);
}


double ProfileExponential::getQuantile(double p) {
  return boost::math::quantile(profile, p);
}


double ProfileExponential::getMGF(double t) {
  assert(t != profile.lambda());
  return 1 / (1 - t / profile.lambda());
}


double ProfileExponential::getSample() {
  // Create a Mersenne twister random number generator
  // that is seeded once with #seconds since 1970
  static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
 
  // select Exponential probability distribution
  boost::exponential_distribution<double> dist(profile.lambda());
 
  // bind random number generator to distribution, forming a function
  boost::variate_generator<boost::mt19937&, boost::exponential_distribution<double> >  sampler(rng, dist);
  
  // sample from the distribution
  return sampler();
}


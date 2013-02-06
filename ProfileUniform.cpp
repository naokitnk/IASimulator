#include "Profile.h"
#include "ProfileUniform.h"


ProfileUniform::ProfileUniform(boost::math::uniform profile) : Profile() {
  this->profile = profile;
}


double ProfileUniform::getMean() {
  return boost::math::mean(profile);
}


double ProfileUniform::getVariance() {
  return boost::math::variance(profile);
}


double ProfileUniform::getPDF(double x) {
  return boost::math::pdf(profile, x);
}


double ProfileUniform::getCDF(double x) {
  return boost::math::cdf(profile, x);
}


double ProfileUniform::getQuantile(double p) {
  return boost::math::quantile(profile, p);
}


double ProfileUniform::getMGF(double t) {
  return (exp(t * profile.upper()) - exp(t * profile.lower())) / (t * (profile.upper() - profile.lower()));
}


double ProfileUniform::getSample() {
  // Create a Mersenne twister random number generator
  // that is seeded once with #seconds since 1970
  static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
 
  // select Uniform probability distribution
  boost::uniform_real<double> dist(profile.lower(), profile.upper());
 
  // bind random number generator to distribution, forming a function
  boost::variate_generator<boost::mt19937&, boost::uniform_real<double> >  sampler(rng, dist);
  
  // sample from the distribution
  return sampler();
}


#include "Profile.h"
#include "ProfileUniform.h"
#include "ProfileZAGA.h"


ProfileZAGA::ProfileZAGA(boost::math::gamma_distribution<double> profile, double q) : Profile(), profile(profile.shape(), profile.scale()) {
  assert(0 <= q && q <= 1);
  this->profile = profile;
  this->q = q;
}


double ProfileZAGA::getMean() {
  return q * boost::math::mean(profile);
}


double ProfileZAGA::getVariance() {
  return q * boost::math::mean(profile) * boost::math::mean(profile) * (1 - q + 1 / profile.shape());
}


double ProfileZAGA::getPDF(double x) {
  assert(x >= 0);
  if (x == 0) {
    return 1 - q;
  } else {
    return q * boost::math::pdf(profile, x);
  }
}


double ProfileZAGA::getCDF(double x) {
  assert(x >= 0);
  if (x == 0) {
    return 1 - q;
  } else {
    return (1 - q) + q * boost::math::cdf(profile, x);
  }
}


double ProfileZAGA::getQuantile(double p) {
  assert(0 <= p && p <= 1);
  if (p <= 1 - q && q == 0) {
    return 0;
  } else {
    return boost::math::quantile(profile, (p - (1 - q)) / q);
  }
}


double ProfileZAGA::getMGF(double t) {
  assert(t < 1 / profile.scale());
  return (1 - q) + q * pow(1 - t * profile.scale(), -profile.shape());
}


double ProfileZAGA::getSample() {
  ProfileUniform profile_uniform = ProfileUniform(boost::math::uniform(0, 1.0));
  double random_probability = profile_uniform.getSample();


  if (random_probability < 1 - q) {
    return 0;
  } else {
    // Create a Mersenne twister random number generator
    // that is seeded once with #seconds since 1970
    static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
 
    // select ZAGA probability distribution
    boost::gamma_distribution<double> dist(profile.shape(), profile.scale());
 
    // bind random number generator to distribution, forming a function
    boost::variate_generator<boost::mt19937&, boost::gamma_distribution<double> >  sampler(rng, dist);
  
    // sample from the distribution
    return sampler();
  }
}


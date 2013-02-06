#include "Profile.h"
#include "ProfileNormal.h"


ProfileNormal::ProfileNormal(boost::math::normal profile) : Profile() {
  this->profile = profile;
}


double ProfileNormal::getMean() {
  return boost::math::mean(profile);
}


double ProfileNormal::getVariance() {
  return boost::math::variance(profile);
}


double ProfileNormal::getPDF(double x) {
  return boost::math::pdf(profile, x);
}


double ProfileNormal::getCDF(double x) {
  return boost::math::cdf(profile, x);
}


double ProfileNormal::getQuantile(double p) {
  return boost::math::quantile(profile, p);
}


double ProfileNormal::getMGF(double t) {
  return exp(t * boost::math::mean(profile) + boost::math::variance(profile) * t * t / 2);
}


double ProfileNormal::getSample() {
  // Create a Mersenne twister random number generator
  // that is seeded once with #seconds since 1970
  static boost::mt19937 rng(static_cast<unsigned> (std::time(0)));
 
  // select Normal probability distribution
  boost::normal_distribution<double> dist(boost::math::mean(profile), sqrt(boost::math::variance(profile)));
 
  // bind random number generator to distribution, forming a function
  boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> >  sampler(rng, dist);
  
  // sample from the distribution
  return sampler();
}


double ProfileNormal::getProbabilityMassRisk() {
  const int n = 10000;
  const double x_min = -1000;
  const double x_max = 0;
  return getIntegralBySimpson(x_min, x_max, n);
}


double ProfileNormal::f(double x) {
  return x * boost::math::pdf(profile, x);
}


double ProfileNormal::getIntegralBySimpson(double x_min, double x_max, int n) {
  double delta = (x_max - x_min) / n;
  double a;
    
  a = f(x_min);
  a += f(x_min + delta * n);
    
  int i;
  for(i = 1; i < n; i += 2){
    a += 4.0 * f(x_min + delta * i);
  }
  for(i = 2; i < n; i += 2){
    a += 2.0 * f(x_min + delta * i);
  }

  return a * delta / 3.0;
}

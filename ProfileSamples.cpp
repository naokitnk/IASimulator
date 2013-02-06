#include "Profile.h"
#include "ProfileSamples.h"
#include "ProfileUniform.h"


ProfileSamples::ProfileSamples() : Profile() {
  this->mean = 0;
  this->variance = 0;
}


ProfileSamples::ProfileSamples(std::vector<double> samples) : Profile() {
  this->samples = samples;
  mean = 0;
  variance = 0;
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    mean += *it;
  }
  mean /= (samples).size();
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    variance += pow(*it - mean, 2);
  }
  variance /= samples.size();
}


void ProfileSamples::addSample(double sample) {
  samples.push_back(sample);

  mean = 0;
  variance = 0;
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    mean += *it;
  }
  mean /= (samples).size();
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    variance += pow(*it - mean, 2);
  }
  variance /= samples.size();
}


void ProfileSamples::setMean() {
  mean = 0;
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    mean += *it;
  }
  mean /= samples.size();
}


void ProfileSamples::setVariance() {
  variance = 0;
  for (std::vector<double>::iterator it = samples.begin(); it != samples.end(); it++) {
    variance += pow(*it - mean, 2);
  }
  variance /= samples.size();
}


double ProfileSamples::getMean() {
  return mean;
}


double ProfileSamples::getVariance() {
  return variance;
}


double ProfileSamples::getPDF(double x) {
  // need to implement
  return 0;
}


double ProfileSamples::getCDF(double x) {
  // need to implement
  return 0;
}


double ProfileSamples::getQuantile(double p) {
  // need to implement
  return 0;
}


double ProfileSamples::getMGF(double t) {
  // need to implement
  return 0;
}


double ProfileSamples::getSample() {
  ProfileUniform profile_uniform = ProfileUniform(boost::math::uniform(0, samples.size()));
  int index = profile_uniform.getSample();
  if (index == samples.size()) {
    index = profile_uniform.getSample();
  }
  return samples[index];
}


double ProfileSamples::getExponentialPremium(double alpha) {
  // need to implement
  return 0;
}


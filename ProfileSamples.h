#ifndef PROFILESAMPLES_H_
#define PROFILESAMPLES_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileSamples : public Profile {
 public:
  ProfileSamples();
  ProfileSamples(std::vector<double> samples);
  void addSample(double sample);
  void setMean();
  void setVariance();
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

  double getExponentialPremium(double alpha);


 protected:
   std::vector<double> samples;
   double mean, variance;
};
#endif

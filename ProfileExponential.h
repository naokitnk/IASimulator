#ifndef PROFILEEXPONENTIAL_H_
#define PROFILEEXPONENTIAL_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileExponential : public Profile {
 public:
  ProfileExponential(boost::math::exponential profile);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

 protected:
   boost::math::exponential profile;
};
#endif

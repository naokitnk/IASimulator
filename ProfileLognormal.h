#ifndef PROFILELOGNORMAL_H_
#define PROFILELOGNORMAL_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileLognormal : public Profile {
 public:
  ProfileLognormal(boost::math::lognormal profile);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

 protected:
   boost::math::lognormal profile;
};
#endif

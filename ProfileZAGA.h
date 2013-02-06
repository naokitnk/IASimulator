#ifndef PROFILEZAGA_H_
#define PROFILEZAGA_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileZAGA : public Profile {
 public:
  ProfileZAGA(boost::math::gamma_distribution<double> profile, double q = 1);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

 protected:
   boost::math::gamma_distribution<double> profile;
   double q;
};
#endif

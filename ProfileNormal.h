#ifndef PROFILENORMAL_H_
#define PROFILENORMAL_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileNormal : public Profile {
 public:
  ProfileNormal(boost::math::normal profile);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

  double getProbabilityMassRisk();

 protected:
   boost::math::normal profile;

 private:
   double f(double x);
   double getIntegralBySimpson(double x_min, double x_max, int n);
};
#endif

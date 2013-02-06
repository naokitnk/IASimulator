#ifndef PROFILEUNIFORM_H_
#define PROFILEUNIFORM_H_

#include <ctime>
#include <boost/math/distributions.hpp>
#include <boost/random.hpp>


class Profile;


class ProfileUniform : public Profile {
 public:
  ProfileUniform(boost::math::uniform profile);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

 protected:
   boost::math::uniform profile;
};
#endif

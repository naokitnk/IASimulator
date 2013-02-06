#ifndef PROFILEDOUBLE_H_
#define PROFILEDOUBLE_H_


class Profile;


class ProfileDouble : public Profile {
 public:
  ProfileDouble(double profile);
  double getMean();
  double getVariance();
  double getPDF(double x);
  double getCDF(double x);
  double getQuantile(double p);
  double getMGF(double t);
  double getSample();

  double getExponentialPremium(double alpha);


 protected:
  double profile;
};
#endif

#ifndef PROFILE_H_
#define PROFILE_H_

#include <cassert>
#include <math.h>


class Profile {
 public:
  Profile();
  virtual ~Profile() = 0;
  virtual double getMean() = 0;
  virtual double getVariance() = 0;
  virtual double getPDF(double x) = 0;
  virtual double getCDF(double x) = 0;
  virtual double getQuantile(double p) = 0;
  virtual double getMGF(double t) = 0;
  virtual double getSample() = 0;

  double getNetPremium();
  double getExpectedValuePremium(double theta);
  double getVariancePremium(double alpha);
  double getStandardDeviationPremium(double beta);
  double getExponentialPremium(double alpha);

  //virtual double getProbabilityMassRisk() = 0;

 protected:
};
#endif

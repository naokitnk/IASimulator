#ifndef PRINCIPAL_H_
#define PRINCIPAL_H_

#include "Utility.h"
#include "UtilityLinear.h"
#include "UtilityQuadratic.h"
#include "UtilityLogarithmic.h"
#include "UtilityExponential.h"
#include "UtilityPower.h"

#include "Profile.h"
#include "ProfileDouble.h"
#include "ProfileUniform.h"
#include "ProfileNormal.h"
#include "ProfileLognormal.h"
#include "ProfileExponential.h"
#include "ProfileSamples.h"


class Simulator;


class Principal {
 public:
  Principal(Simulator *sim);
  Principal(Simulator *sim, double capital);
  ~Principal();
  void setCapital(double capital);
  double increaseCapital(double delta);
  double decreaseCapital(double delta);
  double getCapital();
  void setUtilityLinear();
  void setUtilityQuadratic(double c);
  void setUtilityLogarithmic();
  void setUtilityExponential(double alpha);
  void setUtilityPower(double c);
  double getUtility();
  double getUtility(double dx);
  double getRiskAversionCoefficient(double dx);


 protected:
  Simulator *simulator;
  double capital;
  Utility *utility_function;
};
#endif

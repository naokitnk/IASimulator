#ifndef UTILITYPOWER_H_
#define UTILITYPOWER_H_

#include <cmath>


class Utility;


class UtilityPower : public Utility {
 public:
  UtilityPower(double c);
  double getUtility(double x);
  double getRiskAversionCoefficient(double x);

 private:
  double c;
};
#endif

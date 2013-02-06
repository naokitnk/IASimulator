#ifndef UTILITYQUADRATIC_H_
#define UTILITYQUADRATIC_H_

#include <cmath>


class Utility;


class UtilityQuadratic : public Utility {
 public:
  UtilityQuadratic(double c);
  double getC();
  double getUtility(double x);
  double getRiskAversionCoefficient(double x);

 private:
  double c;
};
#endif

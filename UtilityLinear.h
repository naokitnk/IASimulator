#ifndef UTILITYLINEAR_H_
#define UTILITYLINEAR_H_


class Utility;


class UtilityLinear : public Utility {
 public:
  UtilityLinear();
  double getUtility(double x);
  double getRiskAversionCoefficient(double x);
};
#endif

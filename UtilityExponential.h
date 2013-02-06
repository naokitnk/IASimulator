#ifndef UTILITYEXPONENTIAL_H_
#define UTILITYEXPONENTIAL_H_

#include <cmath>


class Utility;


class UtilityExponential : public Utility {
 public:
  UtilityExponential(double alpha);
  double getAlpha();
  double getUtility(double x);
  double getRiskAversionCoefficient(double x);

 private:
  double alpha;
};
#endif

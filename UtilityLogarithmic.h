#ifndef UTILITYLOGARITHMIC_H_
#define UTILITYLOGARITHMIC_H_

#include <cmath>


class Utility;


class UtilityLogarithmic : public Utility {
 public:
  //UtilityLogarithmic(double alpha);
  UtilityLogarithmic();
  double getUtility(double x);
  double getRiskAversionCoefficient(double x);

 private:
  //double alpha;
};
#endif

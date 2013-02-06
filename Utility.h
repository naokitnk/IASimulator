#ifndef UTILITY_H_
#define UTILITY_H_

#include <cassert>


class Utility {
 public:
  Utility();
  virtual double getUtility(double x) = 0;
  virtual double getRiskAversionCoefficient(double x) = 0;

 protected:
};
#endif

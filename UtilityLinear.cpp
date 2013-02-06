#include "Utility.h"
#include "UtilityLinear.h"


UtilityLinear::UtilityLinear() : Utility() {

}


double UtilityLinear::getUtility(double x) {
  return x;
}


double UtilityLinear::getRiskAversionCoefficient(double x) {
  return 0;
}


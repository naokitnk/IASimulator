#include "Principal.h"


Principal::Principal(Simulator *sim) {
  this->simulator = sim;
  this->capital = 0;
}


Principal::Principal(Simulator *sim, double capital) {
  this->simulator = sim;
  this->capital = capital;
}


Principal::~Principal() {
}


void Principal::setCapital(double capital) {
  this->capital = capital;
}


double Principal::increaseCapital(double delta) {
  this->capital += delta;
  return this->capital;
}


double Principal::decreaseCapital(double delta) {
  this->capital -= delta;
  return this->capital;
}


double Principal::getCapital() {
  return this->capital;
}


void Principal::setUtilityLinear() { 
  this->utility_function = new UtilityLinear();
}


void Principal::setUtilityQuadratic(double c) { 
  this->utility_function = new UtilityQuadratic(c);
}


void Principal::setUtilityLogarithmic() { 
  this->utility_function = new UtilityLogarithmic();
}


void Principal::setUtilityExponential(double alpha) { 
  this->utility_function = new UtilityExponential(alpha);
}


void Principal::setUtilityPower(double c) { 
  this->utility_function = new UtilityPower(c);
}


double Principal::getUtility() { 
  return this->utility_function->getUtility(this->capital);
}


double Principal::getUtility(double dx) { 
  return this->utility_function->getUtility(this->capital + dx);
}


double Principal::getRiskAversionCoefficient(double dx) { 
  return this->utility_function->getRiskAversionCoefficient(this->capital + dx);
}


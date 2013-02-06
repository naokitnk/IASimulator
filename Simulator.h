#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <boost/math/distributions.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "Principal.h"
#include "Authority.h"
#include "Producer.h"
#include "Consumer.h"

#include "Profile.h"
#include "ProfileDouble.h"
#include "ProfileUniform.h"
#include "ProfileNormal.h"
#include "ProfileLognormal.h"
#include "ProfileExponential.h"
#include "ProfileZAGA.h"
#include "ProfileSamples.h"


class Simulator {
 public:
  Simulator(const char* param_filename);
  ~Simulator();
  int getNumberOfProducers();
  int getNumberOfConsumers();
  virtual std::string runSimulation() = 0;


 protected:
  boost::property_tree::ptree pt;
  int num_producer, num_consumer;
  Authority *authority;
  std::vector<Producer *> producers;
  std::vector<Consumer *> consumers;
  std::stringstream output_stream;


 private:
  void setParameters();
};
#endif

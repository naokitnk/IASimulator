#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "Simulator.h"
#include "SimulatorOneRound.h"
#include "SimulatorDiscreteEvent.h"


int main (int argc, char* argv[]) {
  if (argc < 4 || argc > 5) {
    std::cerr << "Usage: " << argv[0] << " sim_type param_filename out_filename [count] " << std::endl;
    return EXIT_FAILURE;
  }

  int sim_type = boost::lexical_cast<int>(argv[1]);
  const char* param_filename = argv[2];
  const char* out_filename = argv[3];
  int count = 0;

  if (sim_type == 0) {
    if (argc != 5) {
      std::cerr << "count parameter is required for One-Round Simulation" << std::endl;
      return EXIT_FAILURE;
    }
    count = boost::lexical_cast<int>(argv[4]);
  } else if (sim_type == 1) {
    // nothing to do
  } else if (sim_type == 2) {
    if (argc != 5) {
      std::cerr << "count parameter is required for Discrete Event Simulation (Multiple)" << std::endl;
      return EXIT_FAILURE;
    }
    count = boost::lexical_cast<int>(argv[4]);
  } else {
    std::cerr << "sim_type is invalid" << std::endl;
    return EXIT_FAILURE;
  }
  
  std::string result;
  if (sim_type == 0) {
    std::cout << "One-Round Simulation" << std::endl;
    for (int i = 0; i < count; i++) {
    std::cout << "count = " << i << std::endl;
      SimulatorOneRound simulator(param_filename);
      result += simulator.runSimulation();
    }
  } else if (sim_type == 1) {
    std::cout << "Discrete Event Simulation (Single)" << std::endl;
    SimulatorDiscreteEvent simulator(param_filename,  true);
    result += simulator.runSimulation();
  } else if (sim_type == 2) {
    std::cout << "Discrete Event Simulation (Multiple)" << std::endl;
    for (int i = 0; i < count; i++) {
      SimulatorDiscreteEvent simulator(param_filename, false);
      result += simulator.runSimulation();
    }
  }
 
  std::ofstream fout;
  fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
  try {
    fout.open(out_filename, std::ios::trunc);
  } catch (std::ofstream::failure e) {
    std::cerr << "Exception opening output file" << std::endl;
  }
  fout << result;
  fout.close();

  return 0;
}


#ifndef SIMULATORONEROUND_H_
#define SIMULATORONEROUND_H_

#include "Simulator.h"


class SimulatorOneRound : public Simulator {
 public:
  SimulatorOneRound(const char* param_filename);
  ~SimulatorOneRound();
  std::string runSimulation();


 private:
};
#endif

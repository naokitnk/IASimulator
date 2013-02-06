#ifndef SIMULATORDISCRETEEVENT_H_
#define SIMULATORDISCRETEEVENT_H_

#include <queue>

#include "Simulator.h"

#include "Event.h"
#include "EventNull.h"
#include "EventPayDividend.h"
#include "EventArrive.h"
#include "EventFixCost.h"
#include "EventFixValue.h"
#include "EventUpdateStep.h"


class SimulatorDiscreteEvent : public Simulator {
 public:
  SimulatorDiscreteEvent(const char* param_filename, bool single_run = true);
  ~SimulatorDiscreteEvent();
  unsigned int getDuration();
  unsigned int getTime();
  void generateEventArrive(int j);
  void addArrivedPair(int i, int j);
  void payDividend();
  void fixCost(int i, int j);
  void fixValue(int i, int j);
  void updateStep();
  std::string runSimulation();


 private:
  unsigned int duration, current_time;
  bool single_run;
  double prev_capital_authority;
  int count_ruin;
  std::priority_queue<Event*, std::vector<Event*, std::allocator<Event*> >, EventComparison> eventQueue;
  std::vector<std::pair<int, int> > arrived_indices;

  double calculateBarrier();
  void updateLowestCapital();
  void outputCurrentCapitals();
  void checkRuin();
  void handleConsumers();
  int getNewStep(int current_step, int count_claim);
};
#endif

#include "Event.h"
#include "EventFixCost.h"
#include "SimulatorDiscreteEvent.h"


EventFixCost::EventFixCost(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx) : Event(sim, t) {
  producer_index = producer_idx;
  consumer_index = consumer_idx;
}


void EventFixCost::processEvent() {
  std::cout << "cost of information sharing between producer[" << producer_index << "] and consumer[" << consumer_index << "] is about to be fixed at time " << time << std::endl;

  simulator->fixCost(producer_index, consumer_index);
}

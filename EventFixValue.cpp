#include "Event.h"
#include "EventFixValue.h"
#include "SimulatorDiscreteEvent.h"


EventFixValue::EventFixValue(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx) : Event(sim, t) {
  producer_index = producer_idx;
  consumer_index = consumer_idx;
}


void EventFixValue::processEvent() {
  std::cout << "value of information sharing between producer[" << producer_index << "] and consumer[" << consumer_index << "] is about to be fixed at time " << time << std::endl;

  simulator->fixValue(producer_index, consumer_index);
}

#include "Event.h"
#include "EventArrive.h"
#include "SimulatorDiscreteEvent.h"


EventArrive::EventArrive(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx) : Event(sim, t) {
  producer_index = producer_idx;
  consumer_index = consumer_idx;
}


void EventArrive::processEvent() {
  std::cout << "consumer[" << consumer_index << "] arrived to obtain information from producer[" << producer_index << "] at time " << time << std::endl;

  simulator->addArrivedPair(producer_index, consumer_index);
}

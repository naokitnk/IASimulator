#include "Event.h"
#include "SimulatorDiscreteEvent.h"


Event::Event(SimulatorDiscreteEvent *sim, unsigned int t) {
  simulator = sim;
  time = t;
}


Event::~Event() {
}


unsigned int Event::getTime() {
  return time;
}

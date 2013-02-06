#include "Event.h"
#include "EventPayDividend.h"
#include "SimulatorDiscreteEvent.h"


EventPayDividend::EventPayDividend(SimulatorDiscreteEvent *sim, unsigned int t) : Event(sim, t) {
}


void EventPayDividend::processEvent() {
  simulator->payDividend();
}

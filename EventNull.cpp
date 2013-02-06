#include "Event.h"
#include "EventNull.h"
#include "SimulatorDiscreteEvent.h"


EventNull::EventNull(SimulatorDiscreteEvent *sim, unsigned int t) : Event(sim, t) {
}


void EventNull::processEvent() {
}

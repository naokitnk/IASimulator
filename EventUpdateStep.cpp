#include "Event.h"
#include "EventUpdateStep.h"
#include "SimulatorDiscreteEvent.h"


EventUpdateStep::EventUpdateStep(SimulatorDiscreteEvent *sim, unsigned int t) : Event(sim, t) {
}


void EventUpdateStep::processEvent() {
  std::cout << "Consumers' steps are about to be updated at time " << time << std::endl;

  simulator->updateStep();
}

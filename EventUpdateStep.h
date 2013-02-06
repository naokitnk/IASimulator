#ifndef EVENTUPDATESTEP_H_
#define EVENTUPDATESTEP_H_


class SimulatorDiscreteEvent;


class EventUpdateStep : public Event {
 public:
  EventUpdateStep(SimulatorDiscreteEvent *sim, unsigned int t);
  void processEvent();

 private:
};
#endif

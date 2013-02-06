#ifndef EVENTNULL_H_
#define EVENTNULL_H_


class SimulatorDiscreteEvent;


class EventNull : public Event {
 public:
  EventNull(SimulatorDiscreteEvent *sim, unsigned int t);
  void processEvent();
};
#endif

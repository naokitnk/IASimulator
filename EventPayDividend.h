#ifndef EVENTPAYDIVIDEND_H_
#define EVENTPAYDIVIDEND_H_


class SimulatorDiscreteEvent;


class EventPayDividend : public Event {
 public:
  EventPayDividend(SimulatorDiscreteEvent *sim, unsigned int t);
  void processEvent();
};
#endif

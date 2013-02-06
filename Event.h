#ifndef EVENT_H_
#define EVENT_H_


class SimulatorDiscreteEvent;


class Event {
 public:
  Event(SimulatorDiscreteEvent *sim, unsigned int t);
  virtual ~Event() = 0;
  virtual void processEvent() = 0;
  unsigned int getTime();

 protected:
  SimulatorDiscreteEvent *simulator;
  unsigned int time;
};


struct EventComparison {
  bool operator () (Event *left, Event *right) {
    return left->getTime() > right->getTime();
  }
};
#endif

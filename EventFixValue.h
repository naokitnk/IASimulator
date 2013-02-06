#ifndef EVENTFIXVALUE_H_
#define EVENTFIXVALUE_H_


class SimulatorDiscreteEvent;


class EventFixValue : public Event {
 public:
  EventFixValue(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx);
  void processEvent();

 private:
  int producer_index, consumer_index;
};
#endif

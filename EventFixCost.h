#ifndef EVENTFIXCOST_H_
#define EVENTFIXCOST_H_


class SimulatorDiscreteEvent;


class EventFixCost : public Event {
 public:
  EventFixCost(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx);
  void processEvent();

 private:
  int producer_index, consumer_index;
};
#endif

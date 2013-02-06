#ifndef EVENTARRIVE_H_
#define EVENTARRIVE_H_


class SimulatorDiscreteEvent;


class EventArrive : public Event {
 public:
  EventArrive(SimulatorDiscreteEvent *sim, unsigned int t, int producer_idx, int consumer_idx);
  void processEvent();

 private:
  int producer_index, consumer_index;
};
#endif

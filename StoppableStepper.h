#ifndef STOPPABLE_STEPPER_H_
#define STOPPABLE_STEPPER_H_

#include "Sensor.h"
#include <Stepper.h>

class StoppableStepper : public Stepper{
 public:
  StoppableStepper(int steps, int pin1, int pin2, int pin3, int pin4);
  virtual ~StoppableStepper(){}
  int stepWithStopper(int number_of_steps);
  void stop();
  void powerOff();

 private:
  StoppableStepper();
  void step(int number_of_steps);

 private:
  volatile bool stop_flag_;
};

#endif // STOPPABLE_STEPPER_H_

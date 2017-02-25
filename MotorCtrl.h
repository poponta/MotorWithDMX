#ifndef MOTOR_CTRL_H_
#define MOTOR_CTRL_H_

#include "StoppableStepper.h"

class MotorCtrl {
 public:
  MotorCtrl(StoppableStepper &stepper);
  ~MotorCtrl(){}
  void setSpeed(long rpms);
  bool moveToInitPos();
  bool movePos(int target);
  bool off();

private:
 MotorCtrl();

 private:
  static const int kMotorStepMax = 32767;
  StoppableStepper &stepper_;
  int current_pos_;
  int target_pos_;
};
#endif

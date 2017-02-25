#include <Arduino.h>
#include "MotorCtrl.h"

StoppableStepper::StoppableStepper(int steps,
				    int pin1,
				    int pin2,
				    int pin3,
				    int pin4) :
  Stepper(steps, pin1, pin2, pin3, pin4), stop_flag_(false) {
}

int StoppableStepper::stepWithStopper(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
  int steps_cnt = 0; // for return value

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { this->direction = 1; }
  if (steps_to_move < 0) { this->direction = 0; }

  // decrement the number of steps, moving one step each time:
  while ((steps_left > 0) && (stop_flag_ == false))
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->step_delay)
    {
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      if (this->pin_count == 5) {
        stepMotor(this->step_number % 10);
      } else {
        stepMotor(this->step_number % 4);
      }
    }
  }
  stop_flag_ = false;

  // calculate how many steps have been taken as a result:
  if (this->direction == 1) {
    steps_cnt = steps_to_move - steps_left;
  } else {
    steps_cnt = steps_to_move + steps_left;
  }
  
  return steps_cnt;
}

void StoppableStepper::stop() {
  stop_flag_ = true;
}

void StoppableStepper::powerOff() {
  digitalWrite(motor_pin_1, LOW);
  digitalWrite(motor_pin_2, LOW);
  digitalWrite(motor_pin_3, LOW);
  digitalWrite(motor_pin_4, LOW);
  step_number = 0;
}

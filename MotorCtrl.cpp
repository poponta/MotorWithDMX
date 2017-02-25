#include "StoppableStepper.h"
#define DMX_STEP_TBL_DEFINE
#include "DmxStepTable.h"
#include "MotorCtrl.h"

MotorCtrl::MotorCtrl(StoppableStepper &stepper) :
  stepper_(stepper),
  current_pos_(0),
  target_pos_(0) {
}

void MotorCtrl::setSpeed(long rpms) {
  stepper_.setSpeed(rpms);
}

bool MotorCtrl::moveToInitPos() {
  stepper_.stepWithStopper(kMotorStepMax*(-1));
  current_pos_ = 0;
}

bool MotorCtrl::movePos(int target) {
  if ((target < 0) || (DMX_STEP_TBL_SIZE <= target)) {
    return false;
  }

  target_pos_ = kCorrespondenceTable[target];
  int diff = target_pos_ - current_pos_;
  if(diff != 0) {
    current_pos_ += stepper_.stepWithStopper(diff);
  }
  
  return true;
}

bool MotorCtrl::off() { 
  stepper_.powerOff();  
}

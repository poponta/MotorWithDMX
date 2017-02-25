//
//  Copyright (c) 2017 Hirotaka Yuno <create.future.technology@gmail.com>.  All right reserved.
//

#include <SoftwareSerial.h>
#include "StoppableStepper.h"
#include "SystemMain.h"
#include "Sensor.h"
#include "MainTask.h"
#include "MotorCtrl.h"

#include "ReceiverInterface.h"
#include "DmxReceiver.h"

#define STEPS (400)
#define GEAR_DIAMETER (16)
#define MOTOR_RPM (103)

#define DMX_CHANNELS      (10)
#define DMX_START_ADDRESS (1)
#define DMX_POS_CHANNEL   (1)
#define DMX_SPEED_CHANNEL (2)

ReceiverInterface *rcv_if;
SoftwareSerial debug_serial(8,9);

// create instance of dmx receiver
DmxReceiver dmx_receiver(DMX_CHANNELS,
		     DMX_START_ADDRESS,
		     DMX_POS_CHANNEL,
		     DMX_SPEED_CHANNEL);

StoppableStepper stepper(STEPS, 4, 5, 6, 7);
MotorCtrl mtr_ctrl(stepper);

void sensor_irq() {
  stepper.stop();
}

int speed_modify(int speed) {
  int ret;
  ret = speed >> 1;
  if(ret < 10) {
    ret = 10;
  }
  return ret;
}

// the setup routine runs once when you press reset:
void MainTask::setup() {

  // Set receiver configration
  rcv_if = &dmx_receiver;
  rcv_if->init();
  
  // Set motor configration
  mtr_ctrl.setSpeed(MOTOR_RPM);

  // Set Interrupt Configuration
  attachInterrupt(1, sensor_irq, RISING);

  // Set Debug Serial
  debug_serial.begin(115200);
}

// the loop routine runs over and over again forever:
void MainTask::loop() 
{
  static SystemState state = kWaitInit;
  static int target_pos = 0;
  static int prev_pos = 0;
  static int target_speed = MOTOR_RPM;
  
  // State Machine
  switch(state) {
    case kWaitInit:
      delay(500);
      state = kMoveInitPosition;
      break;
    
    case kMoveInitPosition:
      mtr_ctrl.moveToInitPos();
      mtr_ctrl.off();
      delay(500);
      state = kStandby;
      break;
    
    case kStandby:
      target_pos = rcv_if->getPos();
      target_speed = speed_modify(rcv_if->getSpeed());
      if(prev_pos != target_pos)  {
        prev_pos = target_pos;
        debug_serial.print("target pos:");
        debug_serial.print(target_pos);
        debug_serial.print(" ");
        debug_serial.print("speed:");
        debug_serial.println(target_speed);
        state = kMove;
      }
      break;
    
    case kMove:
      mtr_ctrl.setSpeed(target_speed);
      mtr_ctrl.movePos(target_pos);
      mtr_ctrl.off();
      state = kStandby;
      break;
    
    case kFinalize:
    break;
    
    case kError:
    break;
    
    default:
    break;
  }
}

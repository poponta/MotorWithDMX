#include <arduino.h>
#include "SystemCommon.h"
#include "Sensor.h"

Sensor::Sensor(int pin, bool is_positive, bool is_pullup) : 
        pin_(pin), is_positive_(is_positive), is_pullup_(is_pullup) {  
  if (is_pullup_ == true) {
    pinMode(pin_, INPUT_PULLUP);
  } else {
    pinMode(pin_, INPUT);
  }
}

Sensor::~Sensor() {
  
}

DigitalState Sensor::getState() const {
  int state = digitalRead(pin_);
    
  if (is_positive_ == true) {
    return static_cast<DigitalState>(state);
  } else {
    return static_cast<DigitalState>(!state);
  }
}

bool Sensor::getSetting(int *pin, bool *is_positive, bool *is_pullup) const {
  if (pin_ == -1) {
    return false;
  } 

  *pin = pin_;
  *is_positive = is_positive_;
  *is_pullup = is_pullup_;  

  return true;
}


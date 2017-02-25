#ifndef SENSOR_H_
#define SENSOR_H_

#include "SystemCommon.h"

class Sensor {
 public:
  Sensor(int pin = -1, bool is_positive = true, bool is_pullup = false);
  virtual ~Sensor();
  DigitalState getState() const;
  bool getSetting(int *pin, bool *is_positive, bool *is_pullup) const;
 private:
  int pin_;
  bool is_positive_;
  bool is_pullup_;
  
};

#endif

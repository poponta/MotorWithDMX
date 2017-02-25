#ifndef DMX_RECEIVER_H_
#define DMX_RECEIVER_H_

#include <inttypes.h>
#include <Conceptinetics.h>
#include "ReceiverInterface.h"

class DmxReceiver : public ReceiverInterface {
 public:
  DmxReceiver(uint16_t channels,
	      uint16_t start_address,
	      uint16_t pos_channel,
	      uint16_t speed_channel);
  ~DmxReceiver(){}
  void init();
  int getPos();
  int getSpeed();
 private:
  DmxReceiver();

 private:
  DMX_Slave *receiver_;
  uint16_t start_address_;
  uint16_t pos_channel_;
  uint16_t speed_channel_;
};
#endif

#include "DmxReceiver.h"

DmxReceiver::DmxReceiver(uint16_t channels,
			 uint16_t start_address,
			 uint16_t pos_channel,
			 uint16_t speed_channel) :
  start_address_(start_address),
  pos_channel_(pos_channel),
  speed_channel_(speed_channel) {
  static DMX_Slave instance(channels);
  receiver_ = &instance;
}

void DmxReceiver::init() {
  receiver_->enable();
  receiver_->setStartAddress(start_address_);
}

int DmxReceiver::getPos() {
  return receiver_->getChannelValue(pos_channel_);
}

int DmxReceiver::getSpeed() {
  return receiver_->getChannelValue(speed_channel_);
}

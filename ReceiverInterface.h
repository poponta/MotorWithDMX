#ifndef RECEIVER_INTERFACE_H_
#define RECEIVER_INTERFACE_H_

class ReceiverInterface {
 public:
  ReceiverInterface(){}
  virtual ~ReceiverInterface(){}
  virtual void init();
  virtual int getPos() = 0;
  virtual int getSpeed() = 0;
};
#endif

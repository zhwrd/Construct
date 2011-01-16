#ifndef CONSTRUCT_CORE_WIRE_H_
#define CONSTRUCT_CORE_WIRE_H_

#include <stdint.h>

namespace construct {
namespace core {

class SignalSocket;
class SignalBuffer;

class Wire {
 public:
  typedef int ID;

  Wire();
  ~Wire();
  
  virtual void Connect(SignalSocket* source, SignalSocket* destination);
  virtual void ChangeSource(SignalSocket* source);
  virtual void ChangeDestination(SignalSocket* destination);
  virtual void CollectData(int num_samples);
  virtual void SetVolume(double volume);
  virtual void SetPan(double pan);

  virtual inline SignalBuffer* buffer() { return buffer_; }
  virtual inline void set_buffer(SignalBuffer* buffer) { buffer_ = buffer; }

 protected:
  virtual void Disconnect(SignalSocket* signalsocket);

  double volume_;
  double pan_;
  double r_volume_;
  double l_volume_;
  SignalSocket* source_;
  SignalSocket* destination_;
  SignalBuffer* buffer_;
};

} // namespace core
} // namespace construct

#endif

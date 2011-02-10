#ifndef SRC_CORE_WIRE_H_
#define SRC_CORE_WIRE_H_

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

  inline double volume() const { return volume_; }
  virtual void set_volume(double volume);
  inline double pan() const { return pan_; }
  virtual void set_pan(double pan);
  inline SignalBuffer* buffer() { return buffer_; }
  inline void set_buffer(SignalBuffer* buffer) { buffer_ = buffer; }

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

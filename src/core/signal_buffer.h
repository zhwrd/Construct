#ifndef SRC_CORE_SIGNAL_BUFFER_H_
#define SRC_CORE_SIGNAL_BUFFER_H_

#include <stdint.h>

namespace construct {
namespace core {

class SignalBuffer {
 public:
  SignalBuffer(int num_samples, int num_channels);
  ~SignalBuffer();

  void Clear();

  double* buffer() const { return buffer_; }
  int num_samples() const { return num_samples_; }
  int num_channels() const { return num_channels_; }
 
 private:
  double* buffer_;
  int num_samples_;
  int num_channels_;
};

} // namespace core
} // namespace construct

#endif

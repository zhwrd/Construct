#ifndef CONSTRUCT_CORE_SIGNAL_BUFFER_H_
#define CONSTRUCT_CORE_SIGNAL_BUFFER_H_

#include <stdint.h>

namespace construct {
namespace core {

class SignalBuffer {
 public:
  SignalBuffer(uint32_t num_samples, uint32_t num_channels);
  ~SignalBuffer();

  void Clear();

  double* buffer() const { return buffer_; }
  uint32_t num_samples() const { return num_samples_; }
  uint32_t num_channels() const { return num_channels_; }
 
 private:
  double* buffer_;
  uint32_t num_samples_;
  uint32_t num_channels_;
};

} // namespace core
} // namespace construct

#endif

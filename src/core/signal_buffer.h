#ifndef CONSTRUCT_CORE_SIGNAL_BUFFER_H_
#define CONSTRUCT_CORE_SIGNAL_BUFFER_H_

namespace construct {
namespace core {

class SignalBuffer {
 public:
  SignalBuffer(int num_samples, int num_channels);
  ~SignalBuffer();

 void Clear();

 double* get_buffer() const { return buffer_; }
 int get_num_samples() const { return num_samples_; }
 int get_num_channels() const { return num_channels_; }
 
 private:
  double* buffer_;
  int num_samples_;
  int num_channels_;
};

} // namespace core
} // namespace construct

#endif

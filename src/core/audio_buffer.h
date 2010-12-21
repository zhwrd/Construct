#ifndef CONSTRUCT_CORE_AUDIO_BUFFER_H_
#define CONSTRUCT_CORE_AUDIO_BUFFER_H_

namespace construct {
namespace core {

class AudioBuffer {
 public:
  AudioBuffer(int num_samples, int num_channels);
  ~AudioBuffer();

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

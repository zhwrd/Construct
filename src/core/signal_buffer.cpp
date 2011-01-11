#include "signal_buffer.h"
#include <utility/dsp.h>
#include <cstdlib>
#include <cassert>

namespace construct {
namespace core {

SignalBuffer::SignalBuffer(int num_samples, int num_channels)
  : num_samples_(num_samples), num_channels_(num_channels) {
  assert(num_samples >= 0);
  assert(num_channels > 0);
  buffer_ = (double*)malloc(num_samples_*num_channels_*sizeof(*buffer_));
}

SignalBuffer::~SignalBuffer() {
  free(buffer_);
}

void SignalBuffer::Clear() {
  utility::dsp::Clear(buffer_, num_samples_*num_channels_);
}

} // namespace core
} // namespace construct

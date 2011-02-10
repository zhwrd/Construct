#include "oscillator.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <utility/math.h>
#include <cmath>

namespace construct {
namespace core {

Oscillator::Oscillator() :  wavetable_index_(0),
                            wavetable_value_(0.0) {
  inputsockets_.push_back(new InputSocket(*this, "Amplitude"));
  inputsockets_.push_back(new InputSocket(*this, "Frequency"));
  inputsockets_.push_back(new InputSocket(*this, "Wavetable"));
}

void Oscillator::GenerateSignal(int num_samples) {
  using namespace utility;
  amplitude().CollectData(num_samples);
  frequency().CollectData(num_samples);
  wavetable().CollectData(num_samples);
  double* amplitude_buffer = amplitude().signalbuffer()->buffer();
  double* frequency_buffer = frequency().signalbuffer()->buffer();
  double* wavetable_buffer = wavetable().signalbuffer()->buffer();
  int wavetable_length = wavetable().signalbuffer()->num_samples();
  int sample_rate = time_info_.sample_rate;
  int num_out_channels = output().signalbuffer()->num_channels();
  for (int i = 0; i < num_samples; ++i) {
    double output_sample = amplitude_buffer[i]*wavetable_value_;
    double increment = (wavetable_length * frequency_buffer[i]) / sample_rate;
    double wavetable_position = wavetable_index_ + increment;
    int index = 0;
    for (int channel = 0; channel < num_out_channels; ++channel) {
      int out_index = i*num_out_channels + channel;
      output().signalbuffer()->buffer()[out_index] = output_sample;
    }
    wavetable_position = fmod(wavetable_position, wavetable_length);
    wavetable_index_ += (int)increment;
    wavetable_index_ %= wavetable_length;
    index = wavetable_index_;
    wavetable_value_ = math::LinearInterpolation(index, index + 1,
                                                 wavetable_buffer[index],
                                                 wavetable_buffer[index + 1],
                                                 wavetable_position);
  }
}

} // namespace core
} // namespace construct

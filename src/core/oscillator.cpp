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
  Amplitude().CollectData(num_samples);
  Frequency().CollectData(num_samples);
  Wavetable().CollectData(num_samples);
  double* amplitude = Amplitude().signalbuffer()->buffer();
  double* frequency = Frequency().signalbuffer()->buffer();
  double* wavetable = Wavetable().signalbuffer()->buffer();
  int wavetable_length = Wavetable().signalbuffer()->num_samples();
  int sample_rate = time_info_.sample_rate;
  int num_out_channels = Output().signalbuffer()->num_channels();
  for (int i = 0; i < num_samples; ++i) {
    double output = amplitude[i]*wavetable_value_;
    double increment = (wavetable_length * frequency[i]) / sample_rate;
    double wavetable_position = wavetable_index_ + increment;
    int index = 0;
    for (int channel = 0; channel < num_out_channels; ++channel) {
      int out_index = i*num_out_channels + channel;
      Output().signalbuffer()->buffer()[out_index] = output;
    }
    wavetable_position = fmod(wavetable_position, wavetable_length);
    wavetable_index_ += (int)increment;
    wavetable_index_ %= wavetable_length;
    index = wavetable_index_;
    wavetable_value_ = math::LinearInterpolation( index, index + 1,
                                                  wavetable[index],
                                                  wavetable[index + 1],
                                                  wavetable_position);
  }
}

} // namespace core
} // namespace construct

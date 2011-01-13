#include "oscillator.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <utility/math.h>

namespace construct {
namespace core {

Oscillator::Oscillator() :  wavetable_position_(0.0),
                            wavetable_index_(0),
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
  for (int i = 0; i < num_samples; ++i) {
    double output = amplitude[i]*wavetable_value_;
    double increment = (wavetable_length * frequency[i]) / 44100.0;
    wavetable_position_ += increment;
    int index = (int)wavetable_position_;
    Output().signalbuffer()->buffer()[i] = output;
    wavetable_index_ = index;
    wavetable_value_ = math::LinearInterpolation( index, index + 1.0,
                                                  wavetable[index],
                                                  wavetable[index + 1],
                                                  wavetable_position_);
    if (wavetable_position_ > wavetable_length - 1) {
      wavetable_index_ = 0;
      wavetable_position_ = 0.0;
    }
  }
}

} // namespace core
} // namespace construct

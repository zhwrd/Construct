#include "oscillator.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

namespace construct {
namespace core {

Oscillator::Oscillator() :  wavetable_position_(0) {
  inputsockets_.push_back(new InputSocket(*this, "Amplitude"));
  inputsockets_.push_back(new InputSocket(*this, "Frequency"));
  inputsockets_.push_back(new InputSocket(*this, "Wavetable"));
}

void Oscillator::GenerateSignal(int num_samples) {
  Amplitude().CollectData(num_samples);
  Frequency().CollectData(num_samples);
  Wavetable().CollectData(num_samples);
  double* amplitude = Amplitude().signalbuffer()->buffer();
  double* frequency = Frequency().signalbuffer()->buffer();
  double* wavetable = Wavetable().signalbuffer()->buffer();
  int wavetable_length = Wavetable().signalbuffer()->num_samples();
  for (int i = 0; i < num_samples; ++i) {
    double output = amplitude[i]*wavetable[wavetable_position_];
    double increment = (wavetable_length * frequency[i]) / 44100.0;
    Output().signalbuffer()->buffer()[i] = output;
    wavetable_position_ += (int)increment;
    wavetable_position_ %= wavetable_length;
  }
}

} // namespace core
} // namespace construct

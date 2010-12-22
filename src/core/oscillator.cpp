#include "oscillator.h"
#include <cstdlib>

namespace construct {
namespace core {

Oscillator::Oscillator() :  wavetable_position_(0) {
  InitializeSockets();
}

void Oscillator::GenerateAudio(int num_samples) {
  double* amplitude = Amplitude().signalbuffer()->buffer();
  double* frequency = Frequency().signalbuffer()->buffer();
  double* wavetable = Wavetable().signalbuffer()->buffer();
  for (int i = 0; i < num_samples; ++i) {
    double output = amplitude[i]*wavetable[wavetable_position_];
    Output().signalbuffer()->buffer()[i] = output;
    ++wavetable_position_;
    wavetable_position_ %= Wavetable().signalbuffer()->num_samples();
  }
}

void Oscillator::InitializeSockets() {
  inputsockets_.push_back(new InputSocket(*this, "Amplitude"));
  inputsockets_.push_back(new InputSocket(*this, "Frequency"));
  inputsockets_.push_back(new InputSocket(*this, "Wavetable"));
  outputsockets_.push_back(new OutputSocket(*this, "Output"));
}

} // namespace core
} // namespace construct

#include "envelope.h"
#include <cassert>
#include <iostream>

namespace construct {
namespace core {

Envelope::Envelope() :  peak_amplitude_(1.0), duration_(1000.0),
                        shape_position_(0) {
  inputsockets_.push_back(new InputSocket(*this, "Shape"));
}

Envelope::~Envelope() {

}

void Envelope::GenerateSignal(int num_samples) {
  //assert(num_samples >= 0);
  double* shape = Shape().signalbuffer()->buffer();
  double resample_rate = 1.0/duration_;
  int shape_length = Shape().signalbuffer()->num_samples();
  for (int i = 0; i < num_samples; ++i) {
    double output = peak_amplitude_*shape[shape_position_];
    Output().signalbuffer()->buffer()[i] = output;
    if (shape_position_ < shape_length - 1) {
      shape_position_ += 1;
    }
  }
}

} // namespace core
} // namespace construct

#include "envelope.h"
#include <cassert>
#include <iostream>
#include <utility/math.h>

namespace construct {
namespace core {

Envelope::Envelope() :  peak_amplitude_(1.0), duration_(1000.0),
                        shape_index_(0), shape_position_(0.0),
                        shape_value_(0.0), repeat_(false) {
  inputsockets_.push_back(new InputSocket(*this, "Shape"));
}

Envelope::~Envelope() {

}

void Envelope::GenerateSignal(int num_samples) {
  using namespace utility;
  double* shape = Shape().signalbuffer()->buffer();
  double resample_rate = 1.0/duration_;
  int shape_length = Shape().signalbuffer()->num_samples();
  double increment = (shape_length * 1.0/(duration_ / 1000.0)) / 44100.0;
  if (shape_length == 1) { 
    shape_value_ = shape[0]; 
  }
  for (int i = 0; i < num_samples; ++i) {
    double output = peak_amplitude_*shape_value_;
    shape_position_ += increment;
    int index = (int)shape_position_;
    Output().signalbuffer()->buffer()[i] = output;
    if (shape_position_ < shape_length - 1) {
      shape_index_ = index;
      shape_value_ = math::LinearInterpolation( index, index + 1.0,
                                                shape[index], shape[index + 1],
                                                shape_position_);
    } else if (repeat_) {
      shape_index_ = 0;
      shape_position_ = 0.0;
    }
  }
}

} // namespace core
} // namespace construct

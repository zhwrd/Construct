#include "envelope.h"
#include <iostream>
#include "utility/math.h"

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
  double* shape_buffer = shape().signalbuffer()->buffer();
  double resample_rate = 1.0/duration_;
  int shape_length = shape().signalbuffer()->num_samples();
  int sample_rate = time_info_.sample_rate;
  double increment = (shape_length * 1.0/(duration_ / 1000.0)) / sample_rate;
  if (shape_length == 1) { 
    shape_value_ = shape_buffer[0]; 
  }
  for (int i = 0; i < num_samples; ++i) {
    double output_sample = peak_amplitude_*shape_value_;
    shape_position_ += increment;
    int index = (int)shape_position_;
    output().signalbuffer()->buffer()[i] = output_sample;
    if (shape_position_ < shape_length - 1) {
      shape_index_ = index;
      shape_value_ = math::LinearInterpolation(index, index + 1.0,
                                               shape_buffer[index],
                                               shape_buffer[index + 1],
                                               shape_position_);
    } else if (repeat_) {
      shape_index_ = 0;
      shape_position_ = 0.0;
    }
  }
}

} // namespace core
} // namespace construct

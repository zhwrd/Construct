#ifndef CONSTRUCT_CORE_ENVELOPE_H_
#define CONSTRUCT_CORE_ENVELOPE_H_

#include "unit_generator.h"
#include <cassert>

namespace construct {
namespace core {

class Envelope : public UnitGenerator {
 public:
  Envelope();
  virtual ~Envelope();

  virtual void GenerateSignal(int num_samples);

  inline void set_peak_amplitude(double peak_amplitude) { 
    assert(peak_amplitude >= 0.0);
    peak_amplitude_ = peak_amplitude;
  }
  inline void set_duration(double duration) {
    assert(duration >= 0.0);
    duration_ = duration;
  }
  inline void set_repeat(bool repeat) { repeat_ = repeat; }

  inline SignalSocket& Shape() const { return *inputsockets_[0]; }
  double peak_amplitude() const { return peak_amplitude_; }
  double duration() const { return duration_; }
  double repeat() const { return repeat_; }

 private:
  double peak_amplitude_;
  double duration_;
  bool repeat_;

  int shape_index_;
  double shape_position_;
  double shape_value_;

};

} // namespace core
} // namespace construct

#endif

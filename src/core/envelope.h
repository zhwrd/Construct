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

  inline SignalSocket& Shape() { return *inputsockets_[0]; }
  double peak_amplitude() { return peak_amplitude_; }
  double duration() { return duration_; }


 private:
  double peak_amplitude_;
  double duration_;
  int shape_position_;

};

} // namespace core
} // namespace construct

#endif

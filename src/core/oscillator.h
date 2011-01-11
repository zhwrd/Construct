#ifndef CONSTRUCT_CORE_OSCILLATOR_H_
#define CONSTRUCT_CORE_OSCILLATOR_H_

#include <core/unit_generator.h>

namespace construct {
namespace core {

class Oscillator : public UnitGenerator {
 public:
  Oscillator();
  virtual ~Oscillator() {}

  virtual void GenerateSignal(int num_samples);
  
  inline SignalSocket& Amplitude() { return *inputsockets_[0]; }
  inline SignalSocket& Frequency() { return *inputsockets_[1]; }
  inline SignalSocket& Wavetable() { return *inputsockets_[2]; }

 protected:
  int wavetable_position_;

};

} // namespace core
} // namespace construct

#endif

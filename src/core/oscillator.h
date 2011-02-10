#ifndef SRC_CORE_OSCILLATOR_H_
#define SRC_CORE_OSCILLATOR_H_

#include <core/unit_generator.h>

namespace construct {
namespace core {

class Oscillator : public UnitGenerator {
 public:
  Oscillator();
  virtual ~Oscillator() {}

  virtual void GenerateSignal(int num_samples);

  inline SignalSocket& amplitude() { return *inputsockets_[0]; }
  inline SignalSocket& frequency() { return *inputsockets_[1]; }
  inline SignalSocket& wavetable() { return *inputsockets_[2]; }

 protected:
  int wavetable_index_;
  double wavetable_value_;

};

} // namespace core
} // namespace construct

#endif

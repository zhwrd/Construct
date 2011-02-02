#ifndef CONSTRUCT_CORE_STEP_GENERATOR_H_
#define CONSTRUCT_CORE_STEP_GENERATOR_H_

#include <core/unit_generator.h>
#include <cassert>

namespace construct {
namespace core {

class StepGenerator {
 public:
  StepGenerator() {
    amplitude_ = 0.0;
  }
  virtual ~StepGenerator();

  inline virtual void GenerateSignal(int num_samples) {
    int num_out_channels = Output().signalbuffer()->num_channels();
    for (int i = 0; i < num_samples; ++i) {
      for (int channel = 0; channel < num_out_channels; ++channel) {
        int out_index = i*num_out_channels + channel;
        Output().signalbuffer()->buffer()[out_index] = amplitude;
      }
    }
  }

  inline void set_amplitude(double amplitude) { amplitude_ = amplitude; }

  inline double amplitude() { return amplitude_; }

 private:
  double amplitude_;

};

} // namespace core
} // namespace construct

#endif

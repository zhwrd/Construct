#ifndef CONSTRUCT_CORE_PLAYER_H_
#define CONSTRUCT_CORE_PLAYER_H_

#include <core/oscillator.h>
#include <core/envelope.h>

namespace construct {

namespace audiodrivers {
class AudioDriver;
} // namespace audiodrivers

namespace core {

class Player {
 public:
  Player();
  ~Player();

  void Initialize();
  static double* AudioWork(void* context, int num_samples);
  double* AudioWork(int num_samples);

  audiodrivers::AudioDriver& driver() { return *driver_; } 
  const audiodrivers::AudioDriver& driver() const { return *driver_; } 
  void set_driver(audiodrivers::AudioDriver& driver);

 private:
  audiodrivers::AudioDriver* driver_;
  double* buffer_;

  Oscillator oscillator_;
  Envelope amp_envelope_;
  Envelope freq_envelope_;

};

} // namespace core
} // namespace construct

#endif

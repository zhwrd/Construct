#ifndef CONSTRUCT_CORE_PLAYER_H_
#define CONSTRUCT_CORE_PLAYER_H_

#include <core/unit_generator.h>

namespace construct {

namespace audiodrivers {
class AudioDriver;
} // namespace audiodrivers

namespace core {

class Player {
 public:
  Player();
  ~Player();

  audiodrivers::AudioDriver& driver() { return *driver_; } 
  const audiodrivers::AudioDriver& driver() const { return *driver_; } 
  void set_driver(audiodrivers::AudioDriver& driver);

  static double* AudioWork(void* context, int num_samples);

 private:
  audiodrivers::AudioDriver* driver_;
  double* buffer_;

};

} // namespace core
} // namespace construct

#endif

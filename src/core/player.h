#ifndef CONSTRUCT_CORE_PLAYER_H_
#define CONSTRUCT_CORE_PLAYER_H_

#include <core/oscillator.h>
#include <core/envelope.h>
#include <core/player_time_info.h>

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

  const PlayerTimeInfo& time_info() const { return time_info_; }
  void set_time_info(PlayerTimeInfo time_info);
  const audiodrivers::AudioDriver& driver() const { return *driver_; } 
  void set_driver(audiodrivers::AudioDriver& driver);
  
 private:
  Oscillator* CreateOscillator(double frequency, double amplitude);

  PlayerTimeInfo time_info_;
  audiodrivers::AudioDriver* driver_;
  double* buffer_;

  std::vector<Oscillator*> oscillators_;
  std::vector<Envelope*> envelopes_;

};

} // namespace core
} // namespace construct

#endif

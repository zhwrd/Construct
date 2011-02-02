#ifndef CONSTRUCT_CORE_PLAYER_TIME_INFO_H_
#define CONSTRUCT_CORE_PLAYER_TIME_INFO_H_

namespace construct {
namespace core {

struct PlayerTimeInfo {
  PlayerTimeInfo() {
    sample_rate = 44100;
    bpm = 120;
    num_channels = 2;
  }
  int num_channels;
  int sample_rate;
  int bpm;
};

} // namespace core
} // namespace construct

#endif

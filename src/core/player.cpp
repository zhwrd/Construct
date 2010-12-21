#include "player.h"
#include <audiodrivers/audiodriver.h>

namespace construct {
namespace core {

Player::Player() : driver_(NULL) {
  using namespace audiodrivers;
  buffer_ = (double*)malloc(kMaxWorkSamples*sizeof(*buffer_));
}

Player::~Player() {

}

void Player::set_driver(audiodrivers::AudioDriver& driver) {
  bool opened = false;
  bool started = false;

  if (driver_) {
    if (driver_->opened()) {
      opened = true;
      if (driver_->started()) {
        started = true;
      }
    }
  }

  if (driver_ == &driver) {
    driver_->Stop();
  } else {
    driver_->Close();
    driver_ = &driver;
  }

  driver_->set_callback(AudioWork, this);
  
  if (started) {
    driver_->Start();
  } else if (opened) {
    driver_->Open();
  }

}

double* Player::AudioWork(void* context, int num_samples) {

}

} // namespace core
} // namespace construct

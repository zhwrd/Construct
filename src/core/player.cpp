#include "player.h"
#include <cmath>
#include <audiodrivers/audiodriver.h>
#include <core/wire.h>

namespace construct {
namespace core {

Player::Player() : driver_(NULL) {
  using namespace audiodrivers;
  buffer_ = (double*)malloc(kMaxWorkSamples*sizeof(*buffer_));
}

Player::~Player() {

}

void Player::Initialize() {
  int num_samples = driver_->playback_settings().num_samples;
  int sample_rate = driver_->playback_settings().sample_rate;
  
  // make freq_envelope shape
  int shape_length = 10;
  SignalBuffer* freq_shape = new SignalBuffer(shape_length, 1);
  for (int i = 0; i < shape_length; ++i) {
    freq_shape->buffer()[i] = 440.0 + ((i/10.0) * 440.0);
  }
  
  // init freq_envelope
  freq_envelope_.Shape().set_signalbuffer(freq_shape);
  freq_envelope_.Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  freq_envelope_.set_duration(1000);
  freq_envelope_.set_repeat(true);
  
  // make amp_envelope shape
  shape_length = 10;
  SignalBuffer* amp_shape = new SignalBuffer(shape_length, 1);
  for (int i = 0; i < shape_length; ++i) {
    //amp_shape->buffer()[i] = (i / 10.0);
    amp_shape->buffer()[i] = 1;
  }
  
  // init amp_envelope
  amp_envelope_.Shape().set_signalbuffer(amp_shape);
  amp_envelope_.Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  amp_envelope_.set_duration(10000);
  amp_envelope_.set_peak_amplitude(0.25);

  // make wavetable
  double length = sample_rate/20;
  double omega = 3.14159*2/length;
  int wavetable_length = (int)length;
  SignalBuffer* wavetable = new SignalBuffer(wavetable_length, 1); 
  for (int i = 0; i < wavetable_length; ++i) {
    wavetable->buffer()[i] = sin(omega*i);
  }

  // init oscillator
  oscillator_.Amplitude().set_signalbuffer(new SignalBuffer(num_samples, 1));
  oscillator_.Frequency().set_signalbuffer(new SignalBuffer(num_samples, 1));
  oscillator_.Wavetable().set_signalbuffer(wavetable);
  oscillator_.Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  
  // connect amp_envelope to amplitude
  Wire* amp_wire = new Wire();
  amp_wire->set_buffer(new SignalBuffer(num_samples, 1));
  amp_wire->Connect(&amp_envelope_.Output(), &oscillator_.Amplitude());
  
  // connect freq_envelope to frequency
  Wire* freq_wire = new Wire();
  freq_wire->set_buffer(new SignalBuffer(num_samples, 1));
  freq_wire->Connect(&freq_envelope_.Output(), &oscillator_.Frequency());
}

double* Player::AudioWork(void* context, int num_samples) {
  return static_cast<Player*>(context)->AudioWork(num_samples);
}

double* Player::AudioWork(int num_samples) {
  oscillator_.Output().CollectData(num_samples);
  return oscillator_.Output().signalbuffer()->buffer();
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
    if (driver_ == &driver) {
      driver_->Stop();
    } else {
      driver_->Close();
      driver_ = &driver;
    }
  } else {
    driver_ = &driver;
  }

  driver_->set_callback(AudioWork, this);
  
  if (started) {
    driver_->Start();
  } else if (opened) {
    driver_->Open();
  }

}

} // namespace core
} // namespace construct

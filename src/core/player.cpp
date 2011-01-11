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
  
  // make envelope shape
  int shape_length = 10*44100;
  SignalBuffer* shape = new SignalBuffer(shape_length, 1);
  for (int i = 0; i < shape_length; ++i) {
    shape->buffer()[i] = (i / (10*44100.0))*0.25;
  }
  // init envelope
  envelope.Shape().set_signalbuffer(shape);
  envelope.Output().set_signalbuffer(new SignalBuffer(num_samples, 1));

  // make wavetable
  double length = sample_rate/20;
  double omega = 3.14159*2/length;
  int wavetable_length = (int)length;
  SignalBuffer* wavetable = new SignalBuffer(wavetable_length, 1); 
  for (int i = 0; i < wavetable_length; ++i) {
    wavetable->buffer()[i] = sin(omega*i);
  }

  // make frequency and amplitude buffers for oscillator
  SignalBuffer* frequency = new SignalBuffer(num_samples, 1);
  SignalBuffer* amplitude = new SignalBuffer(num_samples, 1);
  for (int i = 0; i < num_samples; ++i) {
    frequency->buffer()[i] = 440.0;
    amplitude->buffer()[i] = 0.0;
    //amplitude->buffer()[i] = 0.1;
  }

  oscillator.Amplitude().set_signalbuffer(amplitude);
  oscillator.Frequency().set_signalbuffer(frequency);
  oscillator.Wavetable().set_signalbuffer(wavetable);
  oscillator.Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  
  // connect envelope to amplitude
  Wire* wire = new Wire();
  wire->set_buffer(new SignalBuffer(num_samples, 1));
  wire->Connect(&envelope.Output(), &oscillator.Amplitude());
}

double* Player::AudioWork(void* context, int num_samples) {
  return static_cast<Player*>(context)->AudioWork(num_samples);
}

double* Player::AudioWork(int num_samples) {
  oscillator.GenerateSignal(num_samples);
  return oscillator.Output().signalbuffer()->buffer();
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

#include "player.h"
#include <cmath>
#include <audiodrivers/audio_driver.h>
#include <core/wire.h>
#include <utility/dsp.h>

namespace construct {
namespace core {

Player::Player() : driver_(NULL) {
  using namespace audiodrivers;
  buffer_ = (double*)malloc(kMaxWorkSamples*sizeof(*buffer_));
}

Player::~Player() {

}

void Player::Initialize() {
  //oscillators_.push_back(CreateOscillator(440.00, 0.25));
  oscillators_.push_back(CreateOscillator(261.63, 0.25));
  oscillators_.push_back(CreateOscillator(261.63*2, 0.25));
  oscillators_.push_back(CreateOscillator(392.00, 0.25));
}

double* Player::AudioWork(void* context, int num_samples) {
  return static_cast<Player*>(context)->AudioWork(num_samples);
}

double* Player::AudioWork(int num_samples) {
  utility::dsp::Clear(buffer_, num_samples);
  for ( std::vector<Oscillator*>::iterator i = oscillators_.begin();
        i != oscillators_.end();
        ++i) {
    Oscillator* osc = *i;
    osc->Output().CollectData(num_samples);
    utility::dsp::Add(osc->Output().signalbuffer()->buffer(), 
                      buffer_, num_samples, 1.0);
  }
  return buffer_;
}

void Player::set_time_info(PlayerTimeInfo time_info) {
  time_info_ = time_info;
  // TODO: change unitgenerator time info
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

Oscillator* Player::CreateOscillator(double frequency, double amplitude) {
  int num_samples = driver_->playback_settings().num_samples;
  int sample_rate = driver_->playback_settings().sample_rate;
  
  // make freq_envelope shape
  SignalBuffer* freq_shape = new SignalBuffer(1, 1);
  freq_shape->buffer()[0] = frequency;
  
  // init freq_envelope
  Envelope* freq_envelope = new Envelope();
  freq_envelope->Shape().set_signalbuffer(freq_shape);
  freq_envelope->Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  freq_envelope->set_duration(1000);
  freq_envelope->set_repeat(true);
  
  // make amp_envelope shape
  SignalBuffer* amp_shape = new SignalBuffer(1, 1);
  amp_shape->buffer()[0] = amplitude;
  
  // init amp_envelope
  Envelope* amp_envelope = new Envelope();
  amp_envelope->Shape().set_signalbuffer(amp_shape);
  amp_envelope->Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  amp_envelope->set_duration(1000);
  amp_envelope->set_repeat(true);

  // make wavetable
  int wavetable_length = sample_rate/10;
  double omega = (3.14159*2)/wavetable_length;
  SignalBuffer* wavetable = new SignalBuffer(wavetable_length, 1); 
  for (int i = 0; i < wavetable_length; ++i) {
    wavetable->buffer()[i] = sin(omega*i);
    /*
    if (wavetable->buffer()[i] > 0 ) {
      wavetable->buffer()[i] = 1;
    } else {
      wavetable->buffer()[i] = -1;
    }
    */
  }

  // init oscillator
  Oscillator* oscillator = new Oscillator();
  oscillator->Amplitude().set_signalbuffer(new SignalBuffer(num_samples, 1));
  oscillator->Frequency().set_signalbuffer(new SignalBuffer(num_samples, 1));
  oscillator->Wavetable().set_signalbuffer(wavetable);
  oscillator->Output().set_signalbuffer(new SignalBuffer(num_samples, 1));
  
  // connect amp_envelope to amplitude
  Wire* amp_wire = new Wire();
  amp_wire->set_buffer(new SignalBuffer(num_samples, 1));
  amp_wire->Connect(&amp_envelope->Output(), &oscillator->Amplitude());
  
  // connect freq_envelope to frequency
  Wire* freq_wire = new Wire();
  freq_wire->set_buffer(new SignalBuffer(num_samples, 1));
  freq_wire->Connect(&freq_envelope->Output(), &oscillator->Frequency());

  return oscillator;
}

} // namespace core
} // namespace construct

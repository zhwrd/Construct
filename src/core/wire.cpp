#include "wire.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <core/signal_socket.h>
#include <utility/dsp.h>

namespace construct {
namespace core {

Wire::Wire() :  volume_(1.0), pan_(0.0), r_volume_(1.0), l_volume_(1.0),
                source_(NULL), destination_(NULL), buffer_(NULL) {}

Wire::~Wire() {
  if (source_) Disconnect(source_);
  if (destination_) Disconnect(destination_);
}

void Wire::Connect(SignalSocket* source, SignalSocket* destination) {
  source_ = source;
  destination_ = destination;
  source_->Connect(this);
  destination_->Connect(this);
}

void Wire::ChangeSource(SignalSocket* source) {
  assert(source_);
  Disconnect(source_);
  source_ = source;
  source_->Connect(this);
}

void Wire::ChangeDestination(SignalSocket* destination) {
  assert(destination_);
  Disconnect(destination_);
  destination_ = destination;
  destination_->Connect(this);
}

void Wire::CollectData(int num_samples) {
  source_->CollectData(num_samples);
  utility::dsp::MoveMultiply( source_->signalbuffer()->buffer(),
                              buffer_->buffer(),
                              num_samples, volume_);
}

void Wire::SetVolume(double volume) {
  volume_ = volume;
  if (pan_ > 0.0) {
    r_volume_ = volume;
    l_volume_ = r_volume_*(1.0 - pan_);
  } else {
    l_volume_ = volume;
    r_volume_ = l_volume_*(1.0 + pan_);
  }
}

void Wire::SetPan(double pan) {
  pan_ = pan;
  SetVolume(volume_);
}

void Wire::Disconnect(SignalSocket* signalsocket) {
  if (signalsocket == source_) { source_ = NULL; }
  else if (signalsocket == destination_) { destination_ = NULL; }
  else { return; }
  signalsocket->Disconnect(this);
}

} // namespace core
} // namespace construct

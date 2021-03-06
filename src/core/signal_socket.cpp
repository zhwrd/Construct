#include "signal_socket.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstring>
#include "core/unit_generator.h"

namespace construct {
namespace core {
 
// SignalSocket

SignalSocket::SignalSocket(UnitGenerator& unitgenerator, std::string name)
  : unitgenerator_(unitgenerator), name_(name), signalbuffer_(NULL) {}

SignalSocket::~SignalSocket() {}

void SignalSocket::Connect(Wire* wire) {
  wires_.push_back(wire);
}

void SignalSocket::Disconnect(Wire* wire) {
  std::vector<Wire*>::iterator i(std::find(wires_.begin(), wires_.end(), wire));
  assert(i != wires_.end());
  wires_.erase(i);
}

// InputSocket

InputSocket::InputSocket(UnitGenerator& unitgenerator, std::string name)
  : SignalSocket(unitgenerator, name) {}

void InputSocket::CollectData(int num_samples) {
  for ( std::vector<Wire*>::iterator i = wires_.begin();
        i != wires_.end();
        ++i) {
    Wire* wire = *i;
    wire->CollectData(num_samples);
    memcpy(signalbuffer_->buffer(),
           wire->buffer()->buffer(),
           num_samples*sizeof(*signalbuffer_->buffer()));
  }
}

// OutputSocket

OutputSocket::OutputSocket(UnitGenerator& unitgenerator, std::string name)
  : SignalSocket(unitgenerator, name) {}

void OutputSocket::CollectData(int num_samples) {
  unitgenerator_.GenerateSignal(num_samples);
}

} // namespace core
} // namespace construct

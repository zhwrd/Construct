#include "signal_socket.h"
#include <algorithm>
#include <cassert>

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

void InputSocket::CollectData(int num_samples) {
  for ( std::vector<Wire*>::iterator i = wires_.begin();
        i != wires_.end();
        ++i) {
    (*i)->CollectData(num_samples);
  }
}

// OutputSocket

void OutputSocket::CollectData(int /* num_samples */) {
  // Does nothing
}

} // namespace core
} // namespace construct

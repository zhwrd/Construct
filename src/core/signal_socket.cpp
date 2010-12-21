#include "signal_socket.h"

namespace construct {
namespace core {

SignalSocket::SignalSocket(UnitGenerator& unitgenerator, std::string name)
  : unitgenerator_(unitgenerator), name_(name), signalbuffer_(NULL) {}

SignalSocket::~SignalSocket() {}

void SignalSocket::Connect(Wire* wire) {

}

void SignalSocket::Disconnect(Wire* wire) {

}

} // namespace core
} // namespace construct

#include "unit_generator.h"
#include <cassert>

namespace construct {
namespace core {

UnitGenerator::UnitGenerator() {

}

UnitGenerator::~UnitGenerator() {

}

SignalSocket& UnitGenerator::GetInputSocket(OutputSocket::id_type id) {
  assert(id < inputsockets_.size());
  return *inputsockets_[id];
}

SignalSocket& UnitGenerator::GetOutputSocket(OutputSocket::id_type id) {
  assert(id < outputsockets_.size());
  return *outputsockets_[id];
}

} // namespace core
} // namespace construct

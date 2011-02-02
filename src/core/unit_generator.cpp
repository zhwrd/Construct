#include "unit_generator.h"
#include <cassert>
#include <iostream>

namespace construct {
namespace core {

UnitGenerator::UnitGenerator() {
  outputsockets_.push_back(new OutputSocket(*this, "Output"));
}

UnitGenerator::~UnitGenerator() {

}

void UnitGenerator::GenerateSignal(int num_samples) {
  int num_out_channels = Output().signalbuffer()->num_channels();
  for (int i = 0; i < num_samples; ++i) {
    for (int channel = 0; channel < num_out_channels; ++channel) {
      int out_index = i*num_out_channels + channel;
      Output().signalbuffer()->buffer()[out_index] = 0.0;
    }
  }
}

SignalSocket& UnitGenerator::GetInputSocket(OutputSocket::ID id) {
  assert(id < inputsockets_.size());
  return *inputsockets_[id];
}

SignalSocket& UnitGenerator::GetOutputSocket(OutputSocket::ID id) {
  assert(id < outputsockets_.size());
  return *outputsockets_[id];
}

} // namespace core
} // namespace construct

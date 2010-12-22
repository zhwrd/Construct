#ifndef CONSTRUCT_CORE_UNIT_GENERATOR_H_
#define CONSTRUCT_CORE_UNIT_GENERATOR_H_

#include <core/signal_socket.h>

namespace construct {
namespace core {

class UnitGenerator {
 public:
  UnitGenerator();
  virtual ~UnitGenerator();

  virtual void GenerateAudio(int num_samples) = 0;

  SignalSocket& GetInputSocket(OutputSocket::id_type id);
  SignalSocket& GetOutputSocket(OutputSocket::id_type id);
  uint32_t num_inputsockets() const { return inputsockets_.size(); }
  uint32_t num_outputsockets() const { return outputsockets_.size(); }

 protected:
  virtual void InitializeSockets() {}

  std::vector<InputSocket*> inputsockets_;
  std::vector<OutputSocket*> outputsockets_;
};

} // namespace core
} // namespace construct

#endif

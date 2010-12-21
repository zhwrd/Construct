#ifndef CONSTRUCT_CORE_UNIT_GENERATOR_H_
#define CONSTRUCT_CORE_UNIT_GENERATOR_H_

#include <core/signal_socket.h>

namespace construct {
namespace core {

class UnitGenerator {
 public:
  UnitGenerator();
  virtual ~UnitGenerator();

  uint32_t num_inputsockets() const { return num_inputsockets_; }
  uint32_t num_outputsockets() const { return num_outputsockets_; }

 protected:
  uint32_t num_inputsockets_;
  uint32_t num_outputsockets_;
  InputSocket* inputsockets_;
  OutputSocket* outputsockets_;
};

} // namespace core
} // namespace construct

#endif

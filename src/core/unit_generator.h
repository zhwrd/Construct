#ifndef CONSTRUCT_CORE_UNIT_GENERATOR_H_
#define CONSTRUCT_CORE_UNIT_GENERATOR_H_

#include <core/signal_socket.h>
#include <core/player_time_info.h>

namespace construct {
namespace core {

class UnitGenerator {
 friend class Player;
 public:
  UnitGenerator();
  virtual ~UnitGenerator();

  virtual void GenerateSignal(int num_samples);
  
  inline SignalSocket& Output() { return *outputsockets_[0]; }
  SignalSocket& GetInputSocket(InputSocket::ID id);
  SignalSocket& GetOutputSocket(OutputSocket::ID id);
  inline int num_inputsockets() const { return inputsockets_.size(); }
  inline int num_outputsockets() const { return outputsockets_.size(); }

 protected:
  std::vector<InputSocket*> inputsockets_;
  std::vector<OutputSocket*> outputsockets_;
  PlayerTimeInfo time_info_;

};

} // namespace core
} // namespace construct

#endif

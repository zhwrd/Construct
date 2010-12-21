#ifndef CONSTRUCT_CORE_SIGNAL_SOCKET_H_
#define CONSTRUCT_CORE_SIGNAL_SOCKET_H_

#include <core/signal_buffer.h>
#include <core/unit_generator.h>
#include <core/wire.h>
#include <string>

namespace construct {
namespace core {

class SignalSocket {
 public:
  SignalSocket(UnitGenerator& unitgenerator, std::string name);
  virtual ~SignalSocket();

  virtual void CollectData(int /* num_samples */) {}
  virtual void Connect(Wire* wire);
  virtual void Disconnect(Wire* wire);
  
  virtual inline UnitGenerator& get_unitgenerator() const { 
    return unitgenerator_;
  }
  virtual inline SignalBuffer* get_signalbuffer() const { 
    return signalbuffer_;
  }
  virtual inline void set_signalbuffer(SignalBuffer* signalbuffer) { 
    signalbuffer_ = signalbuffer;
  }
  virtual inline const std::string& get_name() const { return name_; }
  virtual inline void set_name(const std::string& name) { this->name_ = name; }

 private:
  UnitGenerator& unitgenerator_;
  std::string name_;
  SignalBuffer* signalbuffer_;

};

} // namespace core
} // namespace construct

#endif

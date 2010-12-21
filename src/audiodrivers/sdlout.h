#ifndef CONSTRUCT_AUDIODRIVERS_SDLOUT_H_
#define CONSTRUCT_AUDIODRIVERS_SDLOUT_H_

#include <stdint.h>
#include <SDL/SDL_audio.h>
#include <audiodrivers/audiodriver.h>

namespace construct {
namespace audiodrivers {

class SDLOut : public AudioDriver {
 public:
  SDLOut();
  virtual ~SDLOut();
 
 protected:
  virtual void DoStart();
  virtual void DoStop();

 private:
  void FillBuffer(Uint8* output_buffer, int buffer_size);
  static void Process(void* arg, Uint8* output_buffer, int buffer_size);

  int16_t* samples_;

};

} // namespace audiodrivers
} // namespace construct

#endif

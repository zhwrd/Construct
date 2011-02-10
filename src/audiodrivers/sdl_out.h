#ifndef SRC_AUDIODRIVERS_SDL_OUT_H_
#define SRC_AUDIODRIVERS_SDL_OUT_H_

#include <stdint.h>
#include <SDL/SDL_audio.h>
#include <audiodrivers/audio_driver.h>

namespace construct {
namespace audiodrivers {

class SDLOut : public AudioDriver {
 public:
  SDLOut();
  virtual ~SDLOut();

  virtual bool Open();
  virtual void Close();
  virtual bool Start();
  virtual void Stop();

 protected:
  static Uint16 ToSDLFormat(int sample_size);
  static int ToSampleSize(Uint16 sdl_format);

 private:
  void FillBuffer(Uint8* output_buffer, int buffer_size);
  static void Process(void* arg, Uint8* output_buffer, int buffer_size);

  int16_t* samples_;

};

} // namespace audiodrivers
} // namespace construct

#endif

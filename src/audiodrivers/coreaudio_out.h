#ifndef SRC_AUDIODRIVERS_COREAUDIO_OUT_H_
#define SRC_AUDIODRIVERS_COREAUDIO_OUT_H_

#include <audiodrivers/audio_driver.h>
#include <CoreServices/CoreServices.h>
#include <CoreAudio/CoreAudio.h>
#include <AudioUnit/AudioUnit.h>

namespace construct {
namespace audiodrivers {

class CoreAudioOut : public AudioDriver {
 public:
  CoreAudioOut();
  virtual ~CoreAudioOut();

  virtual bool Open();
  virtual void Close();
  virtual bool Start();
  virtual void Stop();

 private:
  bool CreateDefaultAudioUnit();
  void CloseDefaultAudioUnit();
  void FillBuffer(AudioBufferList* io_data, UInt32 num_frames);
  static OSStatus Process(void* inRefCon,
                          AudioUnitRenderActionFlags* ioActionFlags,
                          const AudioTimeStamp* inTimeStamp,
                          UInt32 inBusNumber,
                          UInt32 inNumberFrames,
                          AudioBufferList* ioData);

  AudioUnit output_;
  double* samples_;

};

} // namespace audiodrivers
} // namespace construct

#endif

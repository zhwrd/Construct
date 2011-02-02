#include "coreaudio_out.h"

namespace construct {
namespace audiodrivers {

CoreAudioOut::CoreAudioOut() {

}

CoreAudioOut::~CoreAudioOut() {

}

bool CoreAudioOut::Open() {
  if (opened()) {
    Close();
  }
  if (!CreateDefaultAudioUnit()) {
    return false;
  }
  OSStatus err = noErr;
  AudioStreamBasicDescription streamFormat;
  streamFormat.mSampleRate = playback_settings_.sample_rate;
  streamFormat.mFormatID = kAudioFormatLinearPCM;
  streamFormat.mFormatFlags = kAudioFormatFlagsNativeFloatPacked |
                              kAudioFormatFlagIsNonInterleaved;
  streamFormat.mBytesPerPacket = 4;
  streamFormat.mFramesPerPacket = 1;
  streamFormat.mBytesPerFrame = 4;
  streamFormat.mChannelsPerFrame = playback_settings_.num_channels;
  streamFormat.mBitsPerChannel = 32;

  err = AudioUnitSetProperty( output_,
                              kAudioUnitProperty_StreamFormat,
                              kAudioUnitScope_Input,
                              0,
                              &streamFormat,
                              sizeof(AudioStreamBasicDescription));
  if (err) {
    std::cerr << "Error setting audio unit property." << std::endl;
    return false;
  }
  err = AudioUnitInitialize(output_);
  if (err) {
    std::cerr << "Error initializing audio unit." << std::endl;
    return false;
  }

  Float64 outSampleRate;
  UInt32 size = sizeof(Float64);
  err = AudioUnitGetProperty( output_,
                              kAudioUnitProperty_SampleRate,
                              kAudioUnitScope_Output,
                              0,
                              &outSampleRate,
                              &size);
  if (err) {
    std::cerr << "Error getting audio unit properties." << std::endl;
    return false;
  }

  UInt32 max_frames;
  size = sizeof(max_frames);
  err = AudioUnitGetProperty( output_,
                              kAudioUnitProperty_MaximumFramesPerSlice,
                              kAudioUnitScope_Global,
                              0,
                              &max_frames,
                              &size);
  if (err) {
    std::cerr << "Failed getting max frames" << std::endl;
    return false;
  }

  size = sizeof(streamFormat);
  err = AudioUnitGetProperty( output_,
                              kAudioUnitProperty_StreamFormat,
                              kAudioUnitScope_Input,
                              0,
                              &streamFormat,
                              &size);
  if (err) {
    std::cerr << GetMacOSStatusErrorString(err) << std::endl;
    return false;
  }

  playback_settings_.sample_rate = streamFormat.mSampleRate;
  playback_settings_.num_samples = max_frames;
  playback_settings_.sample_size = 32;
  playback_settings_.num_channels = streamFormat.mChannelsPerFrame;
  std::cout << "Given Settings:\n"
            << "\tIn Sample Rate: " << playback_settings_.sample_rate << "\n"
            << "\tOut Sample Rate: " << outSampleRate << "\n"
            << "\tBuffer Size: " << playback_settings_.num_samples << "\n"
            << "\tSample Format: Float32\n"
            << "\tNum Channels: " << playback_settings_.num_channels
            << std::endl;
  samples_ = (double*)malloc( playback_settings_.num_channels*
                              max_frames*sizeof(*samples_));
  opened_ = true;
  return opened_;
}

void CoreAudioOut::Close() {
  if (opened()) {
    Stop();
    CloseDefaultAudioUnit();
    delete samples_;
    opened_ = false;
  }
}

bool CoreAudioOut::Start() {
  if (opened()) {
    OSStatus err = noErr;
    err = AudioOutputUnitStart(output_);
    if (err) {
      std::cerr << "Error starting audio unit." << std::endl;
      return false;
    }
    started_ = true;
  }
  return started_;
}

void CoreAudioOut::Stop() {
  if (started()) {
    OSStatus err = noErr;
    verify_noerr(AudioOutputUnitStop(output_));
    err = AudioUnitUninitialize(output_);
    if (err) {
      std::cerr << "Error uninitializing audio unit." << std::endl;
      return;
    }
    started_ = false;
  }
}

bool CoreAudioOut::CreateDefaultAudioUnit() {
  OSStatus err = noErr;

  ComponentDescription description;
  description.componentType = kAudioUnitType_Output;
  description.componentSubType = kAudioUnitSubType_DefaultOutput;
  description.componentManufacturer = kAudioUnitManufacturer_Apple;
  description.componentFlags = 0;
  description.componentFlagsMask = 0;

  Component component = FindNextComponent(NULL, &description);
  if (component == NULL) { 
    std::cerr << "Could not find default audio output component." << std::endl;
    return false;
  }

  err = OpenAComponent(component, &output_);
  if (component == NULL) {
    std::cerr << "Could not open default audio output component." << std::endl;
    return false;
  }

  AURenderCallbackStruct input;
  input.inputProc = Process;
  input.inputProcRefCon = this;

  err = AudioUnitSetProperty( output_,
                              kAudioUnitProperty_SetRenderCallback,
                              kAudioUnitScope_Input,
                              0,
                              &input,
                              sizeof(input));
  if (err) {
    std::cerr << "Could not set audio unit callback." << std::endl;
    return false;
  }
  return true;
}

void CoreAudioOut::CloseDefaultAudioUnit() {
  CloseComponent(output_);
}

void CoreAudioOut::FillBuffer(AudioBufferList* io_data, UInt32 num_frames) {
  int num_channels = playback_settings_.num_channels;
  samples_ = callback(num_frames);
  if (num_channels == 1) {
    Float32* in_buffer = static_cast<Float32*>(io_data->mBuffers[0].mData);
    for (int i = 0; i < num_frames; ++i) {
      in_buffer[i] = (float)samples_[i];
    }
  } else if (num_channels == 2) {
    Float32* l_in_buffer = static_cast<Float32*>(io_data->mBuffers[0].mData);
    Float32* r_in_buffer = static_cast<Float32*>(io_data->mBuffers[1].mData);
    for (int i = 0; i < num_frames; ++i) {
      l_in_buffer[i] = samples_[i*num_channels];
      r_in_buffer[i] = samples_[i*num_channels+1];
    }
  }
}

OSStatus CoreAudioOut::Process( void* inRefCon,
                                AudioUnitRenderActionFlags* ioActionFlags,
                                const AudioTimeStamp* inTimeStamp,
                                UInt32 inBusNumber,
                                UInt32 inNumberFrames,
                                AudioBufferList* ioData) {
  CoreAudioOut* driver = static_cast<CoreAudioOut*>(inRefCon);
  driver->FillBuffer(ioData, inNumberFrames);
  return noErr;
}

} // namespace audiodrivers
} // namespace construct

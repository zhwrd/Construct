cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR})

add_library(audiodrivers  audio_driver.h audio_driver.cpp
  #                          sdl_out.h sdl_out.cpp
                          coreaudio_out.h coreaudio_out.cpp
                          )

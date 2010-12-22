cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR})

add_library(core  signal_buffer.h signal_buffer.cpp
                  signal_socket.h signal_socket.cpp
                  wire.h wire.cpp
                  player.h player.cpp
                  unit_generator.h unit_generator.cpp
                  oscillator.h oscillator.cpp
                  )

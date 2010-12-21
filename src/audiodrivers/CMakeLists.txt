cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR})

add_library(audiodrivers  audiodriver.h audiodriver.cpp
                          sdlout.h sdlout.cpp
                          )

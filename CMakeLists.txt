project(Construct)
cmake_minimum_required(VERSION 2.6)

#find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include(cmake/configure.cmake)
include_directories(. src)
add_subdirectory(src)

if(APPLE)
  #set(DEP_SRCS "deps/SDLMain.m")
  find_library(CORESERVICES_LIBRARY CoreServices)
  find_library(COREAUDIO_LIBRARY CoreAudio)
  find_library(AUDIOUNIT_LIBRARY AudioUnit)
  find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
  mark_as_advanced( CORESERVICES_LIBRARY
                    COREAUDIO_LIBRARY
                    AUDIOUNIT_LIBRARY
                    AUDIOTOOLBOX_LIBRARY)
  set(EXTRA_LIBS  ${CORESERVICES_LIBRARY}
                  ${COREAUDIO_LIBRARY}
                  ${AUDIOUNIT_LIBRARY}
                  ${AUDIOTOOLBOX_LIBRARY})
#else(APPLE)
endif(APPLE)

add_executable(Construct  src/main.cpp
                          ${DEP_SRCS})

target_link_libraries(Construct ${EXTRA_LIBS}
                                ${OPENGL_LIBRARIES}
                                ${SDL_LIBRARIES}
                                core
                                audiodrivers)

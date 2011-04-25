project(Construct)
cmake_minimum_required(VERSION 2.6)

# Include additional cmake files
include(cmake/configure.cmake)

# Set OpenGL
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

# Set Apple frameworks
find_library(CORESERVICES_LIBRARY CoreServices)
find_library(COREAUDIO_LIBRARY CoreAudio)
find_library(AUDIOUNIT_LIBRARY AudioUnit)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
mark_as_advanced( CORESERVICES_LIBRARY
                  COREAUDIO_LIBRARY
                  AUDIOUNIT_LIBRARY
                  AUDIOTOOLBOX_LIBRARY)
set(EXTRA_LIBS ${CORESERVICES_LIBRARY}
               ${COREAUDIO_LIBRARY}
               ${AUDIOUNIT_LIBRARY}
               ${AUDIOTOOLBOX_LIBRARY})

if (CMAKE_HOST_APPLE)
  set(DEP_SRCS "deps/SDLMain.m")
endif()

include_directories(. src)
add_subdirectory(src)

add_executable(Construct  src/main.cpp
                          ${DEP_SRCS})
target_link_libraries(Construct ${EXTRA_LIBS}
                                ${OPENGL_LIBRARIES}
                                ${SDL_LIBRARY}
                                core
                                audiodrivers
                                frontend)

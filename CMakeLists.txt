project(Construct)
cmake_minimum_required(VERSION 2.6)

# Include additional cmake files
include(cmake/configure.cmake)

# Set Qt & OpenGL
find_package(OpenGL REQUIRED)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(-DQT_NO_KEYWORDS)
set(QT_USE_QTOPENGL true)
include_directories(${QT_QTOPENGL_INCLUDE_DIR})

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

include_directories(. src)
add_subdirectory(src)

add_executable(Construct  src/main.cpp)
target_link_libraries(Construct ${EXTRA_LIBS}
                                ${OPENGL_LIBRARIES}
                                ${QT_LIBRARIES}
                                core
                                audiodrivers
                                frontend)

project(Construct)
cmake_minimum_required(VERSION 2.6)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

include(cmake/configure.cmake)

if(CMAKE_HOST_APPLE)
  set(DEP_SRCS "deps/SDLMain.m")
endif()

include_directories(.)
add_subdirectory(src)

add_executable(Construct  src/main.cc
                          ${DEP_SRCS})

target_link_libraries(Construct ${OPENGL_LIBRARIES}
                                ${SDL_LIBRARY}
                                core)

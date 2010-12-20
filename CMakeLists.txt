project(Construct)
cmake_minimum_required(VERSION 2.6)

include_directories(.)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Construct  src/main.cc
                          deps/SDLMain.m)

target_link_libraries(Construct ${OPENGL_LIBRARIES}
                                ${SDL_LIBRARY})

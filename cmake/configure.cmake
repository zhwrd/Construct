# platform specific configuration
#include(CheckIncludeFiles)

#check_include_files("GL/gl.h" HAVE_GL)
#check_include_files("OpenGL/gl.h" HAVE_OPENGL)

if(CMAKE_HOST_APPLE)
  set(HAVE_OPENGL)
else()
  set(HAVE_GL)
endif()

CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/config.h)

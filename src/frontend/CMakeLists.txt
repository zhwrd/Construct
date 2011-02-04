cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR})

set(MOC_HEADERS qgl_construct.h)
#set(UI_FILES .ui)

qt4_wrap_cpp(MOC_OUTFILES ${MOC_HEADERS})
#qt4_wrap_ui(UI_OUTFILES ${UI_FILES})

add_library(frontend  qgl_construct.h qgl_construct.cpp
                      ${MOC_OUTFILES} ${UI_OUTFILES}
                      ct_widget.h ct_widget.cpp
                      )

cmake_minimum_required(VERSION 2.6)
include_directories(${PROJECT_SOURCE_DIR})

add_library(frontend  ct_window.h ct_window.cpp
                      ct_widget.h ct_widget.cpp
                      ct_oscilloscope.h ct_oscilloscope.cpp
                      ct_input_event.h ct_mouse_event.h
                      )

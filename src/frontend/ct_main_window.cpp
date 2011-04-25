#include "ct_main_window.h"
#include <iostream>

namespace construct {
namespace frontend {

CtMainWindow::CtMainWindow() {
  width_ = 400;
  height_ = 400;
}

CtMainWindow::~CtMainWindow() {

}

void CtMainWindow::AddOscilloscope(core::UnitGenerator* unitgenerator) {
  oscilloscope_ = new CtOscilloscope();
  oscilloscope_->set_unitgenerator(unitgenerator);
  oscilloscope_->resize(width_, height_);
}

bool CtMainWindow::Initialize() {
  // Initialize SDL
  const SDL_VideoInfo* info = NULL;
  int bpp = 0;
  int flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "Failed to initialize SDL." << std::endl;
    return false;
  }

  info = SDL_GetVideoInfo();
  if (!info) {
    std::cout << "Failed to get video info." << std::endl;
    return false;
  }
  bpp = info->vfmt->BitsPerPixel;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_Surface* drawContext;
  flags = SDL_OPENGL;
  drawContext = SDL_SetVideoMode(width_, height_, bpp, flags);

  // Intialize OpenGL
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width_, 0, height_, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  return true;
}

void CtMainWindow::Draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  oscilloscope_->Draw();
  SDL_GL_SwapBuffers();
}

} // namespace construct
} // namespace frontend

#include "ct_main_window.h"
#include <iostream>
#include <frontend/ct_mouse_event.h>

namespace construct {
namespace frontend {

CtMainWindow::CtMainWindow() {
  width_ = 400;
  height_ = 400;
}

CtMainWindow::~CtMainWindow() {

}

bool CtMainWindow::Initialize() {
}

void CtMainWindow::Draw() {
}

void CtMainWindow::OnMouseMove(const CtMouseEvent& event) {
}

} // namespace construct
} // namespace frontend

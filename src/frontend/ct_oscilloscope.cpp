#include "ct_oscilloscope.h"
#include <iostream>

namespace construct {
namespace frontend {

CtOscilloscope::CtOscilloscope(CtWidget* parent) : CtWidget(parent) {
  unitgenerator_ = NULL;
  y_sample_ = 0;
}

CtOscilloscope::~CtOscilloscope() {

}

void CtOscilloscope::Draw() {
  if (!unitgenerator_) { return; }
  core::SignalBuffer* output = unitgenerator_->output().signalbuffer();
  int num_samples = output->num_samples();
  double x_scale = (double)width()/num_samples;
  double x_sample = 0;

  // only supports 1 channel for now
  if (output->num_channels() != 1) return;

  glLoadIdentity();
  glTranslatef(0, height()/2, 0);
  glBegin(GL_LINE_STRIP);
    for (int i = 0; i < num_samples; ++i) {
      double sample = output->buffer()[i];
      y_sample_ = sample*(height()/2);
      glColor3ub(255, 0, 0);
      glVertex2d(x_sample, y_sample_);
      x_sample += x_scale;
      glVertex2d(x_sample, y_sample_);
    }
  glEnd();

}

void CtOscilloscope::set_unitgenerator(core::UnitGenerator* unitgenerator) {
  unitgenerator_ = unitgenerator;
}

}  // namespace frontend 
}  // namespace construct

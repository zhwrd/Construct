#include "ct_oscilloscope.h"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "core/unit_generator.h"

namespace construct {
namespace frontend {

CtOscilloscope::CtOscilloscope(CtWidget* parent) : CtWidget(parent) {
  unit_generator_ = NULL;
  y_sample_ = 0;
}

CtOscilloscope::~CtOscilloscope() {
}

void CtOscilloscope::Draw() {
  if (!unit_generator_) { return; }
  core::SignalBuffer* output = unit_generator_->output().signalbuffer();
  int num_samples = output->num_samples();
  double x_scale = (double)width()/num_samples;
  double x_sample = 0;

  // only supports 1 channel for now
  if (output->num_channels() != 1) return;

  glPushMatrix();
  glTranslatef(0, height()/2.0, 0);
	glColor3d(0.5, 0, 0);
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

	glPopMatrix();
}

void CtOscilloscope::set_unit_generator(core::UnitGenerator* unit_generator) {
  unit_generator_ = unit_generator;
}

}  // namespace frontend 
}  // namespace construct

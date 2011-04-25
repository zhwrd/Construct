#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <construct_app.h>
#include "config.h"

int main(int argc, char* argv[]) {
  using namespace construct;

  ConstructApp app;
  app.Initialize();
  return app.Execute();
}

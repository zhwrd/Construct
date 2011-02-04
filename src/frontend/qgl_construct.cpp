#include "qgl_construct.h"

namespace construct {
namespace frontend {

QGLConstruct::QGLConstruct(QWidget* parent) : QGLWidget(parent) {

}

QGLConstruct::~QGLConstruct() {

}

QSize QGLConstruct::minimumSizeHint() const {
  return QSize(100, 100);
}

QSize QGLConstruct::sizeHint() const {
  return QSize(400, 400);
}

void QGLConstruct::initializeGL() {
  qglClearColor(QColor("Black"));
}

void QGLConstruct::paintGL() {

}

void QGLConstruct::resizeGL(int width, int height) {

}

void QGLConstruct::mousePressEvent(QMouseEvent *event) {

}

void QGLConstruct::mouseMoveEvent(QMouseEvent *event) {

}

} // namespace construct
} // namespace frontend

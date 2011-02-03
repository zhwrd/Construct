#ifndef FRONTEND_QGL_CONSTRUCT_H_
#define FRONTEND_QGL_CONSTRUCT_H_

#include <QGLWidget>
#include <QMainWindow>

namespace construct {
namespace frontend {

class QGLConstruct : public QGLWidget {
 Q_OBJECT
 public:
  QGLConstruct(QWidget* parent = NULL);
  virtual ~QGLConstruct();

  virtual QSize minimumSizeHint() const;
  virtual QSize sizeHint() const;

 protected:
  virtual void initializeGL();
  virtual void paintGL();
  virtual void resizeGL(int width, int height);
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);

 private:
};

} // namespace construct
} // namespace frontend

#endif

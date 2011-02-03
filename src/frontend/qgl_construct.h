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
  ~QGLConstruct(); 
};

} // namespace construct
} // namespace frontend

#endif

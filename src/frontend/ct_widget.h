#ifndef SRC_FRONTEND_CT_WIDGET_H_
#define SRC_FRONTEND_CT_WIDGET_H_

#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <frontend/ct_mouse_event.h>

namespace construct {
class ConstructApp;
namespace frontend {

class CtWidget {
 public:
  friend class construct::ConstructApp;
  typedef std::vector<CtWidget*> CtWidgetList;

  explicit CtWidget(CtWidget* parent = NULL);
  virtual ~CtWidget();

  // Child/Parent
  inline CtWidget* parent() const { return parent_; }
  inline const CtWidgetList& children() { return children_; }
  void set_parent(CtWidget* parent);
  void add_child(CtWidget* child);
  void remove_child(CtWidget* child);
  bool is_parent_of(CtWidget* child);

  // States
  inline bool is_window() const { return is_window_; }
  inline bool enabled() const { return enabled_; }
  void set_enabled(bool enabled);

  // Drawing
  void redraw();
  inline bool visible() const { return visible_; }
  void set_visible(bool visible);

  // Geometry
  inline int width() const { return width_; }
  inline int height() const { return height_; }
  inline int x() const { return x_; }
  inline int y() const { return y_; }
  inline void set_geometry(int x, int y, int width, int height) {
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
  }
  inline void resize(int width, int height) {
    width_ = width;
    height_ = height;
  }
  inline void move(int x, int y) {
    x_ = x;
    y_ = y;
  }
  inline int minimum_width() const { return minimum_width_; }
  inline int maximum_width() const { return maximum_width_; }
  inline int minimum_height() const { return minimum_height_; }
  inline int maximum_height() const { return maximum_height_; }
  inline void set_minimum_width(int minimum_width) {
    minimum_width_ = minimum_width;
  }
  inline void set_maximum_width(int maximum_width) {
    maximum_width_ = maximum_width;
  }
  inline void set_minimum_height(int minimum_height) {
    minimum_height_ = minimum_height;
  }
  inline void set_maximum_height(int maximum_height) {
    maximum_height_ = maximum_height;
  }

 protected:
  // Mouse events
  virtual void OnMouseDoubleClick(const CtMouseEvent& event);
  virtual void OnMousePress(const CtMouseEvent& event);
  virtual void OnMouseRelease(const CtMouseEvent& event);
  virtual void OnMouseMove(const CtMouseEvent& event);
  virtual void Draw();

 private:
  CtWidget* parent_;
  CtWidgetList children_;
  bool enabled_;
  bool is_window_;
  bool visible_;
  int width_;
  int height_;
  int x_;
  int y_;
  int minimum_width_;
  int maximum_width_;
  int minimum_height_;
  int maximum_height_;

};

} // namespace frontend
} // namespace construct

#endif

#include "ct_widget.h"
#include <algorithm>

namespace construct {
namespace frontend {

CtWidget::CtWidget(CtWidget* parent) {
  parent_ = parent;
  enabled_ = true;
  is_window_ = false;
  visible_ = true;
  width_ = 0;
  height_ = 0;
  x_ = 0;
  y_ = 0;
  minimum_width_ = 0;
  maximum_width_ = 0;
  minimum_height_ = 0;
  maximum_height_ = 0;
}

CtWidget::~CtWidget() {

}

void CtWidget::set_parent(CtWidget* parent) {
  if (parent_) {
    parent_->remove_child(this);
  }
  parent_ = parent;
}

void CtWidget::add_child(CtWidget* child) {
  children_.push_back(child);
  child->resize(width_, height_);
}

void CtWidget::remove_child(CtWidget* child) {
  std::remove(children_.begin(), children_.end(), child);
}

bool CtWidget::is_parent_of(CtWidget* child) {
  return std::count(children_.begin(), children_.end(), child);
}

void CtWidget::set_enabled(bool enabled) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->set_enabled(enabled);
  }
  enabled_ = enabled;
}

void CtWidget::redraw() {
  Draw();
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->redraw();
  }
}

void CtWidget::set_visible(bool visible) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->set_visible(visible);
  }
  visible_ = visible;
}

void CtWidget::OnMouseDoubleClick(const CtMouseEvent& event) {

}

void CtWidget::OnMousePress(const CtMouseEvent& event) {

}

void CtWidget::OnMouseRelease(const CtMouseEvent& event) {

}

void CtWidget::OnMouseMove(const CtMouseEvent& event) {

}

void CtWidget::Draw() {

}

} // namespace frontend
} // namespace construct

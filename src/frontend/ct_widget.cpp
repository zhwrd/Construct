#include "ct_widget.h"
#include <algorithm>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

namespace construct {
namespace frontend {

CtWidget::CtWidget(CtWidget* parent) {
  parent_ = NULL;
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
  set_parent(parent);
}

CtWidget::~CtWidget() {
  cleanup();
  CtWidgetList children = children_;
  for (CtWidgetList::iterator i = children.begin();
       i != children.end();
       ++i) {
    CtWidget* child = *i;
    delete child;
  }
  children_.clear();
  set_parent(NULL);
}

void CtWidget::set_parent(CtWidget* parent) {
  if (parent_) {
    parent_->remove_child(this);
  }
  parent_ = parent;
  if (parent_) {
    parent_->add_child(this);
    resize(parent_->width(), parent_->height());
  }
}

bool CtWidget::is_parent_of(CtWidget* child) {
  return std::count(children_.begin(), children_.end(), child);
}

void CtWidget::cleanup() {
  for (CtWidgetList::iterator i = invalid_children_.begin();
       i != invalid_children_.end();
       ++i) {
    delete *i;
  }
  invalid_children_.clear();
  for (CtWidgetList::iterator i = children_.begin();
       i != children_.end();
       ++i) {
    (*i)->cleanup();
  }
}

void CtWidget::set_enabled(bool enabled) {
  for (CtWidgetList::iterator i = children_.begin();
       i != children_.end();
       ++i) {
    (*i)->set_enabled(enabled);
  }
  enabled_ = enabled;
}

void CtWidget::redraw() {
  glPushMatrix();
  glTranslatef(x_, y_, 0.0);
  Draw();
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->redraw();
  }
  glPopMatrix();
}

void CtWidget::set_visible(bool visible) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->set_visible(visible);
  }
  visible_ = visible;
}

void CtWidget::invalidate() {
  if (parent_) {
    parent_->invalidate_child(this);
  }
}

void CtWidget::invalidate_child(CtWidget* child) {
  invalid_children_.push_back(child);
}

void CtWidget::OnMouseDoubleClick(const CtMouseEvent& event) {

}

void CtWidget::OnMousePress(const CtMouseEvent& event) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->OnMousePress(event);
  }
}

void CtWidget::OnMouseRelease(const CtMouseEvent& event) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->OnMouseRelease(event);
  }
}

void CtWidget::OnMouseMove(const CtMouseEvent& event) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->OnMouseMove(event);
  }
}

void CtWidget::Draw() {

}

void CtWidget::add_child(CtWidget* child) {
  if (!is_parent_of(child)) {
    children_.push_back(child);
  } 
}

void CtWidget::remove_child(CtWidget* child) {
  CtWidgetList::iterator i = std::find(children_.begin(),
                                       children_.end(),
                                       child);
  if (i != children_.end()) {
    children_.erase(i);
  }
}

} // namespace frontend
} // namespace construct

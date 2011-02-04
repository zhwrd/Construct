#include "ct_widget.h"
#include <algorithm>

namespace construct {
namespace frontend {

CtWidget::CtWidget(CtWidget* parent) {

}

CtWidget::~CtWidget() {

}

void CtWidget::SetParent(CtWidget* parent) {
  if (parent_) {
    parent_->RemoveChild(this);
  }
  parent_ = parent;
}

void CtWidget::AddChild(CtWidget* child) {
  children_.push_back(child);
}

void CtWidget::RemoveChild(CtWidget* child) {
  std::remove(children_.begin(), children_.end(), child);
}

bool CtWidget::IsParentOf(CtWidget* child) {
  return std::count(children_.begin(), children_.end(), child);
}

void CtWidget::SetEnabled(bool enabled) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->SetEnabled(enabled);
  }
  enabled_ = enabled;
}

void CtWidget::Draw() {

}

void CtWidget::Redraw() {

}

void CtWidget::SetVisible(bool visible) {
  for ( CtWidgetList::iterator i = children_.begin();
        i != children_.end();
        ++i) {
    (*i)->SetVisible(visible);
  }
  visible_ = visible;
}

} // namespace frontend
} // namespace construct

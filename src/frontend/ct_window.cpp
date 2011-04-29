#include "ct_window.h"
#include <iostream>
#include "frontend/ct_mouse_event.h"

namespace construct {
namespace frontend {

CtWindow::CtWindow(CtWidget* parent) : CtWidget(parent) {
	window_bar_size_ = 15;
	exit_pressed_ = false;
	move_pressed_ = false;
}

CtWindow::~CtWindow() {
}

void CtWindow::Draw() {
	glPushMatrix();

	// Window background
	glColor3d(0.1, 0.1, 0.1);
	glBegin(GL_QUADS);
		glVertex2d(0, 0);
		glVertex2d(0, height() + window_bar_size_);
		glVertex2d(width(), height() + window_bar_size_);
		glVertex2d(width(), 0);
	glEnd();

	if (exit_pressed_) {
		glColor3d(0, 0.5, 0);
		glBegin(GL_QUADS);
			glVertex2d(0, height());
			glVertex2d(0, height() + window_bar_size_);
			glVertex2d(window_bar_size_, height() + window_bar_size_);
			glVertex2d(window_bar_size_, height());
		glEnd();
	}

	// Window borders
	glColor3d(0, 0.5, 0);
	glBegin(GL_LINES);
		// Left
		glVertex2d(0, 0);
		glVertex2d(0, height() + window_bar_size_);
		// Top
		glVertex2d(0, height());
		glVertex2d(width(), height());
		// Right
		glVertex2d(width(), height() + window_bar_size_);
		glVertex2d(width(), 0);
		// Bottom
		glVertex2d(width(), 0);
		glVertex2d(0, 0);
		// Window bar top
		glVertex2d(0, height() + window_bar_size_);
		glVertex2d(width(), height() + window_bar_size_);
		// Window bar exit button
		glVertex2d(window_bar_size_, height());
		glVertex2d(window_bar_size_, height() + window_bar_size_);
		glVertex2d(0, height() + window_bar_size_);
		glVertex2d(window_bar_size_, height());
	glEnd();

	glPopMatrix();
}

void CtWindow::OnMouseMove(const CtMouseEvent& event) {
	if (move_pressed_) {
		move(x() + event.x_rel, y() + event.y_rel);
	}
}

void CtWindow::OnMousePress(const CtMouseEvent& event) {
	if (in_exit_button(event.x, event.y) && event.buttons == LEFT_BUTTON) {
		exit_pressed_ = true;
	}
	if (in_move_bar(event.x, event.y) && event.buttons == LEFT_BUTTON) {
		move_pressed_ = true;
		move_event_ = event;
	}
}

void CtWindow::OnMouseRelease(const CtMouseEvent& event) {
	if (event.buttons == LEFT_BUTTON) {
		if (in_exit_button(event.x, event.y) && exit_pressed_) {
			invalidate();
		} 
		exit_pressed_ = false;
		move_pressed_ = false;
	}
}

} // namespace construct
} // namespace frontend

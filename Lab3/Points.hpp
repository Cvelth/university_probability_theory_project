#pragma once
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <vector>
#include "Pair.hpp"

class Points : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:
	Points(float margins, QWidget * parent = 0) : m_margins(margins), QOpenGLWidget(parent), m_marked(0.f,0.f) {}
	~Points() {}

	void sendData(Data &data) {
		m_data = data;
		mark(0.f, 0.f);
		update();
	}
	void mark(float x, float y) {
		m_marked = pair<float, float>(x, y);
		update();
	}

protected:
	virtual void initializeGL() override {
		initializeOpenGLFunctions();
		glClearColor(1, 1, 1, 1);
	}
	virtual void resizeGL(GLint w, GLint h) override {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		glOrtho(-m_margins, 2.f * m_margins, -m_margins, 2.f * m_margins, -1, +1);
	}
	virtual void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);

		drawData(GL_POINTS, m_data);
		drawMarked();
		drawCanvas();
	}

	void drawCanvas() {
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex2f(-m_margins, 0.f);
		glVertex2f(2.f * m_margins, 0.f);

		glVertex2f(0.f, -m_margins);
		glVertex2f(0.f, 2.f * m_margins);
		glEnd();
	}
	void drawData(GLenum mode, Data data) {
		glBegin(mode);
		glColor3f(0.f, 0.f, 1.f);
		for each(auto e in *data) {
			glVertex2f(e.k(), e.v());
		}
		glEnd();
	}
	void drawMarked() {
		if (m_marked.k() + m_marked.v() != 0.f) {
			const float STEP = 1.f/200.f;
			glBegin(GL_QUADS);
			glColor3f(1.f, 0.f, 0.f);
			glVertex2f(m_marked.k() - STEP, m_marked.v());
			glVertex2f(m_marked.k(), m_marked.v() + STEP);
			glVertex2f(m_marked.k() + STEP, m_marked.v());
			glVertex2f(m_marked.k(), m_marked.v() - STEP);
			glEnd();
		}
	}

protected:
	Data m_data;
	pair<float, float> m_marked;
	float m_margins;
};

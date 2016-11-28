#pragma once
#include "Data.hpp"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

using Verts = std::vector<std::pair<float, float>>;

class Color {
public:
	float r, g, b, a;
	Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f) : r(r), g(g), b(b), a(a) {}
	void operator()() {
		glColor4f(r, g, b, a);
	}
};

class AbstractCanvas : public QOpenGLWidget, protected QOpenGLFunctions {
private:
	float m_margins;

public:
	AbstractCanvas(float margins, QWidget * parent = 0) : m_margins(margins), QOpenGLWidget(parent) {}

	virtual void sendData(Data &data) abstract;
	
	void repaint() {
		resize(width() + 1, height() + 1);
		update();
		resize(width(), height());
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
		drawCanvas(Color(1.f));
	}

	virtual void drawCanvas(Color color) {
		glBegin(GL_LINES);
		color();
		glVertex2f(-m_margins, 0.f);
		glVertex2f(2.f * m_margins, 0.f);

		glVertex2f(0.f, -m_margins);
		glVertex2f(0.f, 2.f * m_margins);
		glEnd();
	}

	virtual void drawData(GLenum mode, Color color, Verts verts) {
		glBegin(mode);
		color();
		for each(auto e in verts)
			glVertex2f(e.first, e.second);
		glEnd();
	}
};

class Margins {
public:
	float t, b, l, r;

	Margins() { Margins(0); }
	Margins(float m) { set(m); }
	Margins(float tt, float bb, float ll, float rr) { set(tt, bb, ll, rr); }
	Margins(const Margins &m) { set(m); }

	void set(float m) { t = b = l = r = m; }
	void set(float tt, float bb, float ll, float rr) { t = tt; b = bb; l = ll; r = rr; }
	void set(const Margins& m) { t = m.t; b = m.b; l = m.l; r = m.r; }

	void marg(float &f, float q, bool right) {
		if (f != 0)
			f *= q;
		else if (!right)
			f -= q > 1 ? q - 1.f : q;
		else
			f += q > 1 ? q - 1.f : q;
	}
	void margT(float v, float q) { t = v; marg(t, q, 1); }
	void margB(float v, float q) { b = v; marg(b, q, 0); }
	void margL(float v, float q) { l = v; marg(l, q, 0); }
	void margR(float v, float q) { r = v; marg(r, q, 1); }
};
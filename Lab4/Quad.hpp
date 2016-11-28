#pragma once
#include "AbstractCanvas.hpp"

class Quad : public AbstractCanvas {
private:
	Margins m_margin;
	float m_cl, m_cr;
	Flags m_matrix;

public:
	Quad(float margins, float cl = 0.f, float cr = 0.f, QWidget * parent = 0) : m_margin(margins), m_cl(cl), m_cr(cr), AbstractCanvas(margins,parent) {}

	virtual void sendData(Data &data) override {}
	virtual void sendData(float criticalL, float criticalR) { m_cl = criticalL; m_cr = criticalR; }
	virtual void sendData(Flags v) { m_matrix = v; }

	void setMargins(const Margins& m) { m_margin.set(m); }
	
protected:
	virtual void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);

		drawByMatrix();
		//drawByBorders();
	}

	virtual void resizeGL(GLint w, GLint h) override {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		glOrtho(m_margin.l, m_margin.r, 0, 1, -1, +1);
	}

	virtual void drawByBorders() {
		glBegin(GL_QUADS);
		drawQuad(Color(1.f, 1.f, 1.f), m_margin.l, m_cl);
		drawQuad(Color(0.f, 1.f), m_cl, m_cr);
		drawQuad(Color(1.f, 1.f, 1.f), m_cr, m_margin.r);
		glEnd();
	}

	virtual void drawQuad(Color c, float a, float b) {
		glColor4f(c.r, c.g, c.b, c.a);
		glVertex2f(a, 0.f);
		glVertex2f(a, 1.f);
		glVertex2f(b, 1.f);
		glVertex2f(b, 0.f);
	}

	virtual void drawByMatrix() {
		float step = (m_margin.r - m_margin.l) / m_matrix.size();
		glBegin(GL_QUADS);
		for (int i = 0; i < m_matrix.size() - 1 && m_matrix.size() != 0; i++) 
			if (!m_matrix[i])
				drawQuad(Color(1.f,1.f,1.f), m_margin.l + i*step, m_margin.l + (i + 1)*step);
			else if(m_matrix[i] == flag::f)
				drawQuad(Color(0.f, 1.f, 0.f), m_margin.l + i*step, m_margin.l + (i + 1)*step);
			else
				drawQuad(Color(0.f, 0.f, 1.f), m_margin.l + i*step, m_margin.l + (i + 1)*step);		
		glEnd();
	}
};
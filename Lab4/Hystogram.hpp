#pragma once
#include <AbstractCanvas.hpp>

using Cols = std::vector<float>;

class Hystogram : public AbstractCanvas {
private:
	int m_step;
	Data m_data;
	Cols m_cols;
	Verts m_verts;
	Margins m_margin;

public:
	Hystogram(int step, float margins, QWidget* p = 0) : AbstractCanvas(margins, p), m_step(step) {
		m_margin.set(margins);
		m_margin.b = -0.1f;
		m_margin.l = -m_margin.l;
	}

	virtual void sendData(Data &data) override {
		m_data = data;
		m_cols = m_data.divide(m_step + 1);
		m_cols.pop_back();
		generateHystogram();
	}
	void changeStep(int step) {
		m_step = step;
		m_cols = m_data.divide(m_step + 1);
		m_cols.pop_back();
		generateHystogram();
	}

	Margins* margins() {
		return &m_margin;
	}
	void setMargins(const Margins& m) {
		m_margin.set(m);
	}

protected:
	virtual void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);
		drawData(GL_QUADS, Color(0.f,0.f,1.f), m_verts);
		drawData(GL_LINE_STRIP, Color(0.f,1.f), m_verts);
		drawCanvas(Color(1.f));
	}

	virtual void resizeGL(GLint w, GLint h) override {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		glOrtho(m_margin.l, m_margin.r, m_margin.b, m_margin.t, -1, +1);
	}

	virtual void drawCanvas(Color color) override {
		glBegin(GL_LINES);
		color();
		glVertex2f(m_margin.l, 0.f);
		glVertex2f(m_margin.r, 0.f);

		glVertex2f(0.f, m_margin.t);
		glVertex2f(0.f, m_margin.b);
		glEnd();
	}

	virtual void generateHystogram() {
		m_verts.clear();
		float mx = m_data.max();
		float mn = m_data.min();
		float st = (mx - mn) / m_step;

		m_margin.margT(maxCol(m_cols),1.1f);
		m_margin.margL(mn >= 0.f ? 0.f : mn, 1.1f);
		m_margin.margR(mx <= 0.f ? 0.f : mx, 1.1f);
		m_margin.margB(-m_margin.t, 0.1f);

		for (int i = 1; i < m_cols.size() + 1; i++) {
			m_verts.push_back(std::pair<float, float>((i-1) * st + mn, 0.f));
			m_verts.push_back(std::pair<float, float>((i-1) * st + mn, m_cols[i - 1]));
			m_verts.push_back(std::pair<float, float>(i * st + mn, m_cols[i - 1]));
			m_verts.push_back(std::pair<float, float>(i * st + mn, 0.f));
		}
		repaint();
	}

	float maxCol(Cols c) {
		float r = 0.f;
		for (float f : c)
			if (r < f)
				r = f;
		return r;
	}
};
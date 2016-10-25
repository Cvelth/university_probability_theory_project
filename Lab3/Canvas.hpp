#pragma once
#include "Points.hpp"

class Canvas : public Points {
public:
	Canvas(float margins, QWidget * parent = 0) : Points(margins, parent) {}

	template<class Func>
	void sendData(Func f, float x, float l, float r) {
		m_data->clear(); m_free->clear();
		m_data->push_back(pair<float, float>(l, 0));
		const float STEP = (r - l) / 120.f;
		float n = l;
		for (; n <= x; n += STEP) 
			m_data->push_back(pair<float,float>(n, f(n)));
		m_data->push_back(pair<float, float>(n -= STEP, 0));
		m_data->push_back(pair<float, float>(l, 0));
		for (; n <= r; n += STEP)
			m_free->push_back(pair<float, float>(n, f(n)));
		m_free->push_back(pair<float, float>(r, f(r)));
		m_free->push_back(pair<float, float>(r, 0));
		update();
	}

protected:
	virtual void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);

		drawData(GL_POLYGON, m_data);
		drawData(GL_LINE_STRIP, m_free);
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

private:
	Data m_free;

	float m_margins;
};

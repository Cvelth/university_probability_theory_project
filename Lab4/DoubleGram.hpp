#pragma once
#include "Hystogram.hpp"
#include "Quad.hpp"

class DoubleGram {
private:
	Hystogram *h1, *h2;
	Quad *q;

public:
	DoubleGram(int step, float margins, QWidget* p = 0) {
		h1 = new Hystogram(step, margins, p);
		h2 = new Hystogram(step, margins, p);
		q = new Quad(margins);
		equalMargins();
	}

	void sendData(Data d1, Data d2, float cl, float cr) {
		h1->sendData(d1);
		h2->sendData(d2);
		q->sendData(cl, cr);
		equalMargins();
	}
	void sendData(Data d1, Data d2, Flags d3) {
		h1->sendData(d1);
		h2->sendData(d2);
		q->sendData(d3);
		equalMargins();
	}

	void changeStep(int step) {
		h1->changeStep(step);
		h2->changeStep(step);
		equalMargins();
	}

	void equalMargins() {
		h1->setMargins(mx(*h1->margins(), *h2->margins()));
		h2->setMargins(*h1->margins());
		q->setMargins(*h1->margins());
		repaint();
	}

	void repaint() {
		h1->repaint();
		h2->repaint();
		q->repaint();
	}

	Hystogram* get1() { return h1; }
	Hystogram* get2() { return h2; }
	Quad* getQ() { return q; }

	~DoubleGram() {
		delete h1;
		delete h2;
		delete q;
	}

protected:
	static float mx(float a, float b) { return (abs(a) > abs(b) ? a : b); }
	static Margins mx(Margins a, Margins b) { return Margins(mx(a.t, b.t), mx(a.b, b.b), mx(a.l, b.l), mx(a.r, b.r)); }
};
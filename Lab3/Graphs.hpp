#pragma once
#include <QtWidgets>
#include "CustomLawGenerator.hpp"
#include "Canvas.hpp"

class Graphs : public QWidget {
	Q_OBJECT

public:
	Graphs(QWidget *parent = 0) : QWidget(parent) {
		l = new QHBoxLayout();
		w = new QListWidget();

		x = new Canvas(1.f);
		y = new Canvas(1.f);
		p = new Points(0.6f);

		setNumber("20000");

		auto b = new QHBoxLayout();
		b->addWidget(x, 1);
		b->addWidget(y, 1);

		auto v = new QVBoxLayout();
		v->addWidget(w, 1);
		v->addLayout(b, 1);

		l->addLayout(v, 1);
		l->addWidget(p, 1);
		setLayout(l);
		resize(1600, 800);

		connect(w, &QListWidget::clicked, this, &Graphs::sendData);
	}
	~Graphs() {
		delete l;
		delete w;
		delete x;
		delete y;
		delete p;
	}

	Data data() {
		return m_d;
	}

public slots:
	void setNumber(QString s) {
		m_d = fillList(s.toInt());
		p->sendData(m_d);
		emit callBack(m_d);
	}

protected:
	Data& fillList(const int theNUMBER) {
		Data d;
		CustomLawGenerator g;
		for (int i = 0; i < theNUMBER; i++) {
			i = i;
			pair<float, float> p = g([](float x) {
				return 4.f / PI*sqrtf(1.f - (2 * x - 1)*(2 * x - 1));
			}, [](float x) {
				return 1.f / sqrtf(1 - (2 * x - 1)*(2 * x - 1));
			});

			d->push_back(p);
			w->addItem(QString("x = ") + QString::number(p.k()) + ",\ty = " + QString::number(p.v()) + ";");
			d.m_x += p.k();
			d.m_y += p.v();
		}

		d.m_x /= theNUMBER;
		d.m_y /= theNUMBER;

		for (int i = 0; i < theNUMBER; i++) {
			d.D_x += powf(d[i].k() - d.m_x, 2);
			d.D_y += powf(d[i].v() - d.m_y, 2);
			d.cov += (d[i].k() - d.m_x)*(d[i].v() - d.m_y);
		}

		d.D_x /= theNUMBER;
		d.D_y /= theNUMBER;
		d.cov /= theNUMBER;
		return d.R();
	}

protected slots:
	void sendData(const QModelIndex i) {
		const float STEP = 0.01;
		x->sendData([](float x) {
				return 4.f / PI*sqrtf(1.f - (2 * x - 1)*(2 * x - 1));
		}, m_d[i.row()].k(), 0, 1);

		y->sendData([](float x) {
			return 1.f / sqrtf(1 - (2 * x - 1)*(2 * x - 1));
		}, m_d[i.row()].v(),
			-sqrtf(1 - (2 * m_d[i.row()].k() - 1)*(2 * m_d[i.row()].k() - 1)) / 2 + 0.5f,
			+sqrtf(1 - (2 * m_d[i.row()].k() - 1)*(2 * m_d[i.row()].k() - 1)) / 2 + 0.5f);
		p->mark(m_d[i.row()].k(), m_d[i.row()].v());
	}

private:
	QHBoxLayout* l;
	QListWidget* w;

	Canvas* x;
	Canvas* y;
	Points* p;

	Data m_d;

signals:
	void callBack(Data);
};
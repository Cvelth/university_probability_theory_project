#include "GUI.h"
#include "Importer.hpp"
#include "Decider.hpp"

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	d = new DoubleGram(ui.lineEdit_4->text().toInt(), 1.f);
	connect(ui.pushButton_3, &QPushButton::clicked, this, &GUI::calculate);

	ui.verticalLayout_7->addWidget(d->get1(),10);
	ui.verticalLayout_7->addStretch(1);
	ui.verticalLayout_7->addWidget(d->get2(),10);
	ui.verticalLayout_7->addStretch(1);
	ui.verticalLayout_7->addWidget(d->getQ(),1);

	connect(ui.lineEdit_4, &QLineEdit::textChanged, this, &GUI::resizeH);

	connect(ui.pushButton, &QPushButton::clicked, this, &GUI::import1);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &GUI::import2);

	connect(ui.radioButton, &QRadioButton::clicked, this, &GUI::lab2);
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &GUI::lab3);
	connect(ui.radioButton_3, &QRadioButton::clicked, this, &GUI::labN);
	labN();
}

void GUI::lab2(bool b) {
	if (b) {
		ui.label->show();
		ui.lineEdit->show();
		ui.label_3->show();
		ui.lineEdit_3->show();
	}
}
void GUI::lab3(bool b) {
	if (b) {
		ui.label->hide();
		ui.lineEdit->hide();
		ui.label_3->hide();
		ui.lineEdit_3->hide();
	}
}

void GUI::labN(bool b) {
	if (b) {
		ui.label->hide();
		ui.lineEdit->hide();
		ui.label_3->show();
		ui.lineEdit_3->show();
	}
}

void GUI::import1() {
	import(ui.textEdit);
}
void GUI::import2() {
	import(ui.textEdit_2);
}

void GUI::import(QTextEdit * w)
{
	if (ui.radioButton->isChecked())
		w->setText(QString::fromStdString(Importer::import2(ui.lineEdit_2->text().toFloat(), ui.lineEdit->text().toFloat(), ui.lineEdit_3->text().toFloat())));
	if (ui.radioButton_2->isChecked())
		w->setText(QString::fromStdString(Importer::import3(ui.lineEdit_2->text().toFloat())));
	if (ui.radioButton_3->isChecked())
		w->setText(QString::fromStdString(Importer::import1(ui.lineEdit_2->text().toFloat(), ui.lineEdit_3->text().toFloat())));
}

void GUI::crits(Flags y)
{
	float l = 0, r = y.size();
	int i = 0;
	for (;i < y.size() - 1 && y.size() != 0; i++)
		if (y[i] == flag::f && y[i + 1] == flag::s)
			l = i;
	for (;i < y.size() - 1 && y.size() != 0; i++)
		if (y[i] == flag::s && y[i + 1] == flag::f)
			r = i;

	float mn = (d1.min() < d2.min()) ? d1.min() : d2.min();
	float mx = (d1.max() > d2.max()) ? d1.max() : d2.max();
	float step = (mx - mn) / y.size();

	l = mn + l * step;
	r = mn + r * step;

	ui.lineEdit_11->setText(QString::number(l));
	ui.lineEdit_12->setText(QString::number(r));
}

void GUI::errors(Flags f)
{
	float err1 = 0.f, err2 = 0.f;

	const int STEPS = 100;
	float m1 = d1.m(), m2 = d2.m();
	float s1 = d1.s(), s2 = d2.s();
	float mn = (d1.min() < d2.min()) ? d1.min() : d2.min();
	float mx = (d1.max() > d2.max()) ? d1.max() : d2.max();
	float step = (mx - mn) / STEPS;

	std::vector<float> v1 = d1.divide(STEPS), v2 = d1.divide(STEPS);

	for (int i = 0; i < STEPS; i++) {
		if (f[i] == flag::f)
			err2 += v2[i];
		if (f[i] == flag::s)
			err1 += v1[i];
	}
	ui.lineEdit_13->setText(QString::number(err1 / (d1->size() + d2->size())));
	ui.lineEdit_14->setText(QString::number(err2 / (d1->size() + d2->size())));
}

void GUI::resizeH(const QString& s) {
	int i = s.toInt();
	if (i > 0)
		d->changeStep(s.toInt());
}

void GUI::calculate() {
	d1 = Data(ui.textEdit->toPlainText().toStdString());
	d2 = Data(ui.textEdit_2->toPlainText().toStdString());

	Flags y = Decider::criticalY_bs(d1, d2, ui.lineEdit_5->text().toFloat(), ui.lineEdit_6->text().toFloat());
	d->sendData(d1, d2, y);
	
	ui.lineEdit_7->setText(QString::number(d1.m()));
	ui.lineEdit_8->setText(QString::number(d2.m()));
	ui.lineEdit_9->setText(QString::number(d1.s()));
	ui.lineEdit_10->setText(QString::number(d2.s()));

	crits(y);
	errors(y);
}
#include "gui.h"

GUI::GUI(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	c = new Graphs;
	setData(c->data());
	ui.verticalLayout->addWidget(c, 1);
	resize(1600, 903);

	connect(ui.lineEdit, &QLineEdit::textChanged, c, &Graphs::setNumber);
	connect(ui.pushButton, &QPushButton::clicked, this, &GUI::refresh);
	connect(c, &Graphs::callBack, this, &GUI::setData);
}

GUI::~GUI() {}

void GUI::refresh() {
	c->setNumber(ui.lineEdit->text());
}

void GUI::setData(Data d) {
	ui.lineEdit_2->setText(QString::number(d.m_x));
	ui.lineEdit_3->setText(QString::number(d.m_y));
	ui.lineEdit_4->setText(QString::number(d.D_x+=0.2295f));
	ui.lineEdit_5->setText(QString::number(d.D_y+=0.2575f));
	d.S();
	ui.lineEdit_6->setText(QString::number(d.S_x));
	ui.lineEdit_7->setText(QString::number(d.S_y));
	ui.lineEdit_8->setText(QString::number(d.cov+=0.25f));
	d.R();
	ui.lineEdit_9->setText(QString::number(d.Ro));
}
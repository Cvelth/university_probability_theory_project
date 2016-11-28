#pragma once
#include <QtWidgets/QWidget>
#include "ui_GUI.h"
#include "DoubleGram.hpp"
#include "Data.hpp"

class GUI : public QWidget
{
    Q_OBJECT

private:
	Ui::GUIClass ui;
	DoubleGram *d;
	Data d1, d2;

public:
    GUI(QWidget *parent = Q_NULLPTR);
	
protected:
	void import(QTextEdit* w);

	void crits(Flags y);
	void errors(Flags y);

private slots:
	void lab2(bool b = true);
	void lab3(bool b = true);
	void labN(bool b = true);
	void import1();
	void import2();
	void resizeH(const QString& s);

	void calculate();
};

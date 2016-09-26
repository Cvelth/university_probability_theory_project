#ifndef GUI_H
#define GUI_H

#include "AbstractGenerator.hpp"
#include <QtWidgets/QWidget>
#include "ui_gui.h"

class IncorrectInputException {};

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(QWidget *parent = 0);
	~GUI();

protected:
	QString bit(Bit b);

private:
	Ui::GUIClass ui;
	AbstractGenerator* g;
	AbstractTest* t;

protected slots:
	void clear();
	void generate();
	void test();

	void rb1();
	void rb2();
	void rb3();
	void rbOn();
	void rbOff();
};

#endif // GUI_H

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

private:
	Ui::GUIClass ui;
	AbstractGenerator* g;

protected slots:
	void clear();
	void generate();
	void test();
};

#endif // GUI_H

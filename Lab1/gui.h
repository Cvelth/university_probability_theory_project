#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QWidget>
#include "ui_gui.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(QWidget *parent = 0);
	~GUI();

private:
	Ui::GUIClass ui;
};

#endif // GUI_H

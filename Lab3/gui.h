#ifndef GUI_H
#define GUI_H

#include "ui_gui.h"
#include "Graphs.hpp"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(QWidget *parent = 0);
	~GUI();

protected slots:
	void refresh();
	void setData(Data d);

private:
	Graphs* c;
	Ui::GUIClass ui;
};

#endif // GUI_H

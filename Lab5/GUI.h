#pragma once
#include <QtWidgets/QWidget>
#include "ui_GUI.h"

class VisualGraph;

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);
	~GUI();

private:
    Ui::GUIClass ui;
	VisualGraph *m_graph;
};

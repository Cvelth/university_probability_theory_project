#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include "ui_GUI.h"

class ProcessGraph;
class QLineEdit;

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);
	~GUI();

private:
    Ui::GUIClass ui;
	ProcessGraph *m_graph;

private slots:
	void calculate();
	void theoretical();
	void practical();
};

class WeightDialog : public QDialog {
	Q_OBJECT

private:
	QLineEdit* edit;
	QVBoxLayout *layout;

public:
	WeightDialog(QWidget *parent = 0);
	~WeightDialog();

protected:
	virtual void keyPressEvent(QKeyEvent* e) override;

public slots:
	void showDialog(int _x, int _y);

signals:
	void valueChanged(float value);
};
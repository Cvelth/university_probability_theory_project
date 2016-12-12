#include "GUI.h"
#include <QtWidgets>
#include <ProcessGraph.hpp>

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_graph = new ProcessGraph();
	ui.verticalLayout->addWidget(m_graph, 2);
}

GUI::~GUI() {
	delete m_graph;
}

WeightDialog::WeightDialog(QWidget *parent) : QDialog(parent) {
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	setWindowModality(Qt::ApplicationModal);

	if (parent == 0) {
		setAttribute(Qt::WA_NoSystemBackground, true);
		setAttribute(Qt::WA_TranslucentBackground, true);
	}
	setWindowOpacity(0.6);
	
	edit = new QLineEdit;
	layout = new QVBoxLayout;
	layout->addWidget(edit);
	setLayout(layout);
}

WeightDialog::~WeightDialog() {
	delete layout;
	delete edit;
}

void WeightDialog::keyPressEvent(QKeyEvent * e) {
	if (e->key() == Qt::Key::Key_Enter) {
		emit valueChanged(edit->text().toFloat());
	}
	hide();
}

void WeightDialog::showDialog(int _x, int _y) {
	move(_x, _y);
	show();
}
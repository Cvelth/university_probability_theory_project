#include "GUI.h"
#include <QtWidgets>
#include <VisualGraph.hpp>

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_graph = new VisualGraph();
	ui.verticalLayout->addWidget(m_graph, 2);
}

GUI::~GUI() {
	delete m_graph;
}
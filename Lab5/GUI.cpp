#include "GUI.h"
#include <QtWidgets>
#include <ProcessGraph.hpp>
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\lu.hpp>
namespace bnu = boost::numeric::ublas;

using Matrix = bnu::matrix<float, bnu::column_major>;

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_graph = new ProcessGraph();
	ui.verticalLayout->addWidget(m_graph, 2);
	
	connect(ui.pushButton, &QPushButton::clicked, this, &GUI::calculate);
}

float determinant(bnu::matrix<float> m) {
	bnu::permutation_matrix<> pm(m.size1());

	int res = bnu::lu_factorize(m, pm);

	float det = 1.f;
	for (size_t i = 0; i < pm.size(); i++)
		det *= (i == pm(i)) ? m(i, i) : -m(i, i);
	return det;
}

void GUI::calculate() {
	theoretical();
	practical();
}

GUI::~GUI() {
	delete m_graph;
}

void GUI::theoretical() {
	std::vector<float> result;

	Matrix m(m_graph->nodes()->size(),
			 m_graph->nodes()->size(), 0.f);

	for (auto l : *m_graph->links()) {
		m(l->b()->id(), l->b()->id()) -= l->v();
		m(l->e()->id(), l->b()->id()) += l->v();
	}
	for (int i = 0; i < m_graph->nodes()->size(); i++)
		m(m_graph->nodes()->size() - 1, i) = 1.f;

	float det = determinant(m);

	for (int i = 0; i < m_graph->nodes()->size(); i++) {
		Matrix tM = m;
		for (int j = 0; j < m_graph->nodes()->size() - 1; j++)
			tM(j, i) = 0.f;
		tM(m_graph->nodes()->size() - 1, i) = 1.f;
		float tDet = determinant(tM);
		result.push_back(tDet / det);
	}

	int i = 0;
	QString s;
	for (auto it : result)
		s += "p_" + QString::number(i++) + " = "
		+ QString::number(it) + '\n';
	ui.textEdit->setText(s);
}

void GUI::practical() {
	size_t counter = 0;
	std::vector<float> result;
	result.resize(m_graph->nodes()->size());

	std::mt19937_64 gen = std::mt19937_64(std::random_device()());
	std::uniform_real_distribution<float> dist = 
		std::uniform_real_distribution<float>(0.f, 1.f);

	size_t steps = ui.lineEdit->text().toInt();
	Node* position = *m_graph->nodes()->begin();
	for (size_t i = 0; i < steps; i++) {
		float way = dist(gen);
		Link* link = nullptr;
		for (Link* l : *m_graph->links()) {
			if (*l->b() == *position) {
				link = l;
				way -= link->v();
			}
			if (way < 0.f)
				break;
		}

		if (link) {
			result.at(link->b()->id())++;
			counter++;
			position = link->e();
		} else
			break;
	}
	size_t i = 0;
	QString s;
	for (auto it : result)
		s += "p_" + QString::number(i++) + " -> " + QString::number(it) + " -> " + 
					QString::number(float(it) / counter) + "\n";
	ui.textEdit_2->setText(s);
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
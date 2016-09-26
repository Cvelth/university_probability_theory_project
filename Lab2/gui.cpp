#include "gui.h"
#include "BuitInGenerator.hpp"
#include "NormalGenerator.hpp"
#include <string>
#include <qstring.h>
#include <sstream>

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_4, SIGNAL(clicked()), SLOT(clear()));

	connect(ui.pushButton, SIGNAL(clicked()), SLOT(generate()));
	connect(ui.pushButton_2, SIGNAL(clicked()), SLOT(test()));
}

GUI::~GUI()
{

}

void GUI::clear()
{
	ui.textBrowser->clear();
	ui.textBrowser_2->clear();
	ui.radioButton_3->setChecked(true);
}

void GUI::generate()
{
	if (ui.radioButton->isChecked() && ui.lineEdit_2->text() != "" && ui.lineEdit_3->text() != "")
		g = new BuiltInGenerator(ui.lineEdit_2->text().toFloat(), ui.lineEdit_3->text().toFloat());
	else if (ui.radioButton_3->isChecked() && ui.lineEdit_2->text() != "" && ui.lineEdit_3->text() != "")
		g = new NormalGenerator(ui.lineEdit_2->text().toFloat(), ui.lineEdit_3->text().toFloat());
	else
		throw IncorrectInputException();

	QString output = "";
	for (uint64_t i = 0; i < ui.lineEdit->text().toULongLong(); i++)
		output += QString::number((*g)(), 'g', 8) + '\t';

	delete g;

	ui.textBrowser->setText(output);
}

void GUI::test()
{
	float m = 0.f;
	std::istringstream s(ui.textBrowser->toPlainText().toStdString());

	float f;
	int i = 0;
	while (s >> f)
	{
		m += f;
		i++;
	}
	m /= i;

	float sgm = 0; i = 0;
	s.clear();
	s.str(ui.textBrowser->toPlainText().toStdString());
	while (s >> f)
	{
		sgm += powf(f - m, 2.f);
		i++;
	}
	sgm = sqrtf(sgm / i);

	ui.textBrowser_2->setText("m = " + QString::number(m) + "\nSigma = " + QString::number(sgm));

	//t = new Test();

	//std::vector<Bit> v;
	//for each (auto var in ui.textBrowser->toPlainText())
	//	v.push_back(var == '1' ? true : false);

	//t->setSequence(v);
	//ui.textBrowser_2->setText(QString::fromStdString(t->test(ui.lineEdit_4->text().toLongLong())));
}
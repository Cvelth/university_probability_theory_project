#include "gui.h"
#include "BuitInGenerator.hpp"

GUI::GUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_4, SIGNAL(clicked()), SLOT(clear()));

	connect(ui.radioButton, SIGNAL(clicked()), SLOT(rb1()));
	connect(ui.radioButton_2, SIGNAL(clicked()), SLOT(rb2()));
	connect(ui.radioButton_3, SIGNAL(clicked()), SLOT(rb3()));

	connect(ui.pushButton, SIGNAL(clicked()), SLOT(generate()));
	connect(ui.pushButton_2, SIGNAL(clicked()), SLOT(test()));

	connect(ui.radioButton_4, SIGNAL(clicked()), SLOT(rbOff()));
	connect(ui.radioButton_5, SIGNAL(clicked()), SLOT(rbOff()));
	connect(ui.radioButton_7, SIGNAL(clicked()), SLOT(rbOff()));
	connect(ui.radioButton_6, SIGNAL(clicked()), SLOT(rbOn()));
	ui.lineEdit_4->hide();
}

GUI::~GUI()
{

}

QString GUI::bit(Bit b)
{
	return b ? "1" : "0";
}

void GUI::clear()
{
	ui.textBrowser->clear();
	ui.textBrowser_2->clear();
	ui.radioButton_3->setChecked(true);
	ui.radioButton_4->setChecked(true);
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
	for (uint64_t i = 0; i < ui.lineEdit->text().toLongLong(); i++)
		output += (*g)() + '\n';

	delete g;

	ui.textBrowser->setText(output);
}

void GUI::test()
{
	t = new Test();

	std::vector<Bit> v;
	for each (auto var in ui.textBrowser->toPlainText())
		v.push_back(var == '1' ? true : false);

	t->setSequence(v);
	ui.textBrowser_2->setText(QString::fromStdString(t->test(ui.lineEdit_4->text().toLongLong())));
}
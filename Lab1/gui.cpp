#include "gui.h"

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
	if (ui.radioButton->isChecked())
		g = new CGenerator();
	else if (ui.radioButton_2->isChecked() && ui.lineEdit_2->text() != "")
		g = new LFSR_spreaded(ui.lineEdit_2->text().toLongLong());
	else if (ui.radioButton_3->isChecked() && ui.lineEdit_2->text() != "" && ui.lineEdit_3->text() != "")
		g = new TableGenerator(ui.lineEdit_2->text().toLongLong(), ui.lineEdit_3->text().toLongLong(), new CGenerator());
	else
		throw IncorrectInputException();

	QString output = "";
	for (uint64_t i = 0; i < ui.lineEdit->text().toLongLong(); i++)
		output += bit(g->getBit());

	delete g;

	ui.textBrowser->setText(output);
}

void GUI::test()
{
	if (ui.radioButton_4->isChecked())
		t = new FrequencyTest();
	else if (ui.radioButton_5->isChecked())
		t = new DifferentialTest();
	else if (ui.radioButton_6->isChecked())
		t = new RangeTest();
	else if (ui.radioButton_7->isChecked())
		t = new NonlinearTest();
	
	std::vector<Bit> v;
	for each (auto var in ui.textBrowser->toPlainText())
		v.push_back(var == '1' ? true : false);

	t->setSequence(v);
	ui.textBrowser_2->setText(QString::fromStdString(t->test(ui.lineEdit_4->text().toLongLong())));
}

void GUI::rb1()
{
	ui.lineEdit_2->hide();
	ui.lineEdit_3->hide();
}
void GUI::rb2()
{
	ui.lineEdit_2->show();
	ui.lineEdit_3->hide();
}
void GUI::rb3()
{
	ui.lineEdit_2->show();
	ui.lineEdit_3->show();
}

void GUI::rbOn()
{
	ui.lineEdit_4->show();
}
void GUI::rbOff()
{
	ui.lineEdit_4->hide();
}
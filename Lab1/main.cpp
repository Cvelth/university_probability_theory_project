#include "gui.h"
#include <QtWidgets/QApplication>
#include "TableGenerator.h"
#include <fstream>
#include "FrequencyTest.h"
#include "DifferentialTest.h"
#include "NonlinearTest.h"
#include "RangeTest.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUI w;
	w.show();
	return a.exec();
}
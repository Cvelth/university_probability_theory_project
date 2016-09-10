#include "gui.h"
#include <QtWidgets/QApplication>
#include "TableGenerator.h"
#include <fstream>
#include "FrequencyTest.h"
#include "DifferentialTest.h"
#include "NonlinearTest.h"
#include "RangeTest.h"

/* Qt_main
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUI w;
	w.show();
	return a.exec();
}
*/

// Testing main
int main()
{
	TableGenerator g(12, 8);

	std::vector<Bit> v;
	for (int i = 0; i < 15000; i++)
		v.push_back(g.getBit());

	//DifferentialTest ts;
	//FrequencyTest ts;
	RangeTest ts;
	ts.setSequence(v);

	std::string s = ts.test();
	
	return 0;
}
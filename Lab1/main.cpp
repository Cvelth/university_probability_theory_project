#include "gui.h"
#include <QtWidgets/QApplication>
#include "TableGenerator.h"
#include <fstream>
#include "DifferentialTest.h"
#include "NonlinearTest.h"

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
	NonlinearTest ts;
	ts.setSequence(v);

	long double d = ts.test();
	
	return 0;
}
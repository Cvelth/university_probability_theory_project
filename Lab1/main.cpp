#include "gui.h"
#include <QtWidgets/QApplication>
#include "TableGenerator.h"
#include <fstream>
#include "DifferentialTest.h"

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
	//TableGenerator g(12, 8, (new Table())->load());
	TableGenerator g(12, 8);
	//CGenerator g;
	//LFSR_spreaded g(8);

	std::ofstream f("sequence.txt");
	for (int i = 0; i < 15000; i++)
		f << Bit(g.getBit());
	f.close();
	
	DifferentialTest ts;
	ts.setSequence(std::ifstream("sequence.txt"));

	long double d = ts.test();
	

	return 0;
}
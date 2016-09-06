#include "gui.h"
#include <QtWidgets/QApplication>
#include "LFSR_spreaded.h"
#include <fstream>
#include "cGenerator.h"
#include "FrequencyTest.h"

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
	LFSR_spreaded g(7);
	//CGenerator g;

	std::ofstream f("sequence.txt");
	for (int i = 0; i < 100000; i++)
		f << Bit(g.getBit());
	f.close();

	FrequencyTest ts;
	ts.setSequence(std::ifstream("sequence.txt"));

	long double d = ts.test();

	return 0;
}
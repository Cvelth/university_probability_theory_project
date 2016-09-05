#include "gui.h"
#include <QtWidgets/QApplication>
#include "BinaryNumber.h"

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
	BinaryNumber a { 0b1010,0b0000,0b1111,0b1010 };
	std::string s = a.print();

	return 0;
}
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
	BinaryNumber a { 123,15,17,89 }, b { 19,15,88,20,99 };
	BinaryNumber c = a + b;

	return 0;
}
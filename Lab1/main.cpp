#include "gui.h"
#include <QtWidgets/QApplication>
#include "Polynomial.h"

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
	Polynomial p;
	p.generate(6);

	return 0;
}
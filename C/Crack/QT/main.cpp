#include "crack_with_qt.h"
 
int main(int argc, char *argv[]) {
	QApplication app(argc, argv);  

	PlusMinus window;

	window.resize(360, 240);
	window.setWindowTitle("Plus minus");
	window.show();

	return app.exec();
}
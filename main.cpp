//*****************************************************************************
//Includes
#include<QApplication>
#include<QLabel>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.setWindowTitle("Game Player");
	mainWindow.show();

	return app.exec();
}

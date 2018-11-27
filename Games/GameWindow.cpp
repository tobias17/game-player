//*****************************************************************************
//Includes
#include "GameWindow.h"

GameWindow::GameWindow(Engine* engine1, Engine* engine2) : QWidget(0) {
	engineHandlers[p1Engine] = new EngineHandler(engine1);
	engineHandlers[p1Engine]->moveToThread(&workerThread);
	engineHandlers[p2Engine] = new EngineHandler(engine2);
	engineHandlers[p2Engine]->moveToThread(&workerThread);
	workerThread.start();

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	this->setAttribute(Qt::WA_DeleteOnClose);
}

void GameWindow::closeEvent(QCloseEvent *bar) {
	for (int i = p1Engine; i <= p2Engine; i++) engineHandlers[i]->killEngine();
	workerThread.quit();
	workerThread.wait();
}

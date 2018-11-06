//*****************************************************************************
//Includes
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

	games.push_back("Tic Tac Toe");

	TicTacToeSettings_t settings;
	game = new TicTacToeGame(settings);

	list = new QListWidget(this);
	list->setGeometry(QRect(QPoint(GAP_SIZE, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));

	gameSettingsButton = new QPushButton("Game Settings", this);
	QRect buttonGeometry = QRect(QPoint(GAP_SIZE, GAP_SIZE * 2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	gameSettingsButton->setGeometry(buttonGeometry);
	connect(gameSettingsButton, SIGNAL (released()), this, SLOT (test()));

	for (uint i = 0; i < games.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(games.at(i));
		list->addItem(listItem);
	}
	list->setCurrentRow(0);

	this->setFixedSize(GAP_SIZE * 4 + ITEM_WIDTH * 3, GAP_SIZE * 3 + LIST_HEIGHT + BUTTON_HEIGHT);

}

void MainWindow::test() {
	cout << list->currentRow() << "\n";
	game->show();
}

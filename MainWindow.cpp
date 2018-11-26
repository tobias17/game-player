//*****************************************************************************
//Includes
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

	games.push_back("Tic Tac Toe");

	engines.push_back("Human");
	engines.push_back("Random Moves");
	engines.push_back("Naive Tree Search");

	gameList = new QListWidget(this);
	gameList->setGeometry(QRect(QPoint(GAP_SIZE, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));
	p1List = new QListWidget(this);
	p1List->setGeometry(QRect(QPoint(GAP_SIZE*2 + ITEM_WIDTH, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));
	p2List = new QListWidget(this);
	p2List->setGeometry(QRect(QPoint(GAP_SIZE*3 + ITEM_WIDTH*2, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));

	gameSettingsButton = new QPushButton("Game Settings", this);
	QRect geom = QRect(QPoint(GAP_SIZE, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	gameSettingsButton->setGeometry(geom);
	connect(gameSettingsButton, SIGNAL (released()), this, SLOT (gameSettingsButtonHandler()));

	p1SettingsButton = new QPushButton("Player Settings", this);
	geom = QRect(QPoint(GAP_SIZE*2 + ITEM_WIDTH, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	p1SettingsButton->setGeometry(geom);
	connect(p1SettingsButton, SIGNAL (released()), this, SLOT (p1SettingsButtonHandler()));

	p2SettingsButton = new QPushButton("Player Settings", this);
	geom = QRect(QPoint(GAP_SIZE*3 + ITEM_WIDTH*2, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	p2SettingsButton->setGeometry(geom);
	connect(p2SettingsButton, SIGNAL (released()), this, SLOT (p2SettingsButtonHandler()));

	startGameButton = new QPushButton("Start Game", this);
	geom = QRect(QPoint(GAP_SIZE, GAP_SIZE*3 + LIST_HEIGHT + BUTTON_HEIGHT), QSize(ITEM_WIDTH*3 + GAP_SIZE*2, BUTTON_HEIGHT));
	startGameButton->setGeometry(geom);
	connect(startGameButton, SIGNAL (released()), this, SLOT (startGameButtonHandler()));

	for (uint i = 0; i < games.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(games.at(i));
		gameList->addItem(listItem);
	}
	gameList->setCurrentRow(0);

	for (uint i = 0; i < engines.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(engines.at(i));
		p1List->addItem(listItem);
	}
	p1List->setCurrentRow(0);

	for (uint i = 0; i < engines.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(engines.at(i));
		p2List->addItem(listItem);
	}
	p2List->setCurrentRow(0);

	tttSettingsWindow = new TicTacToeSettingsWindow();
	connect(tttSettingsWindow, SIGNAL (sendTicTacToeSettings(TicTacToeSettings_t)), this, SLOT (receiveTicTacToeSettings(TicTacToeSettings_t)));

	this->setFixedSize(GAP_SIZE*4 + ITEM_WIDTH*3, GAP_SIZE*4 + LIST_HEIGHT + BUTTON_HEIGHT*2);

}

void MainWindow::gameSettingsButtonHandler() {
	tttSettingsWindow->hide();
	tttSettingsWindow->setSettings(tttSettings);
	tttSettingsWindow->show();
}

void MainWindow::receiveTicTacToeSettings(TicTacToeSettings_t aSetting) {
	tttSettings = aSetting;
}

void MainWindow::p1SettingsButtonHandler() {
	switch (p1List->currentRow()) {
	case 1:
		randomMoveEngineSettingsControllers[p1Index].showWindow(); break;
	default:
		break;
	}
}

void MainWindow::p2SettingsButtonHandler() {
	switch (p2List->currentRow()) {
	case 1:
		randomMoveEngineSettingsControllers[p2Index].showWindow(); break;
	default:
		break;
	}
}

void MainWindow::startGameButtonHandler() {
	NaiveTreeSearchEngineSettings_t s;
	Engine* e1;
	switch (p1List->currentRow()) {
	case 1:
		e1 = new RandomMoveEngine(randomMoveEngineSettingsControllers[p1Index].getSettings()); break;
	case 2:
		e1 = new NaiveTreeSearchEngine(s); break;
	default:
		e1 = new HumanEngine; break;
	}
	Engine* e2;
	switch (p2List->currentRow()) {
	case 1:
		e2 = new RandomMoveEngine(randomMoveEngineSettingsControllers[p2Index].getSettings()); break;
	case 2:
		e2 = new NaiveTreeSearchEngine(s); break;
	default:
		e2 = new HumanEngine; break;
	}
	TicTacToeGameWindow* game = new TicTacToeGameWindow(tttSettings, e1, e2);
	game->show();
}






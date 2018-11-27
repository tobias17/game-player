//*****************************************************************************
//Includes
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {

	games.push_back("Tic Tac Toe");
	games.push_back("Connect 4");

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

	this->setFixedSize(GAP_SIZE*4 + ITEM_WIDTH*3, GAP_SIZE*4 + LIST_HEIGHT + BUTTON_HEIGHT*2);

}

void MainWindow::gameSettingsButtonHandler() {
	switch (gameList->currentRow()) {
	case 0:
		ticTacToeSettingsController.showWindow(); break;
	case 1:
		connect4SettingsController.showWindow(); break;
	default:
		cout << "returning..." << endl; break;
	}
}

void MainWindow::p1SettingsButtonHandler() {
	generalSettingsHandler(p1Index);
}

void MainWindow::p2SettingsButtonHandler() {
	generalSettingsHandler(p2Index);
}

void MainWindow::generalSettingsHandler(int index) {
	if (index < 0 || index >= 3) {
		return;
	}
	int listIndex = (index == p1Index) ? p1List->currentRow() : p2List->currentRow();
	switch (listIndex) {
	case 1:
		randomMoveEngineSettingsControllers[index].showWindow(); break;
	case 2:
		naiveTreeSearchEngineSettingsControllers[index].showWindow(); break;
	default:
		cout << "breaking..." << endl; break;
	}
}

void MainWindow::startGameButtonHandler() {
	Engine* engines[2];
	for (int i = 0; i < 2; i++) {
		int index = (i == p1Index) ? p1List->currentRow() : p2List->currentRow();
		switch (index) {
		case 0:
			engines[i] = new HumanEngine; break;
		case 1:
			engines[i] = new RandomMoveEngine(randomMoveEngineSettingsControllers[p1Index].getSettings()); break;
		case 2:
			engines[i] = new NaiveTreeSearchEngine(naiveTreeSearchEngineSettingsControllers[p1Index].getSettings()); break;
		default:
			cout << "returning..." << endl; return;
		}
	}

	if (gameList->currentRow() == 0) {
		TicTacToeSettings_t settings = ticTacToeSettingsController.getSettings();
		TicTacToeGameWindow* window = new TicTacToeGameWindow(settings, engines[p1Index], engines[p2Index]);
		window->show();
	} else if (gameList->currentRow() == 1) {
		Connect4Settings_t settings = connect4SettingsController.getSettings();
		Connect4GameWindow* window = new Connect4GameWindow(settings, engines[p1Index], engines[p2Index]);
		window->show();
	}
}






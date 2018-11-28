//*****************************************************************************
//Includes
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	// add all of the supported games to the vector
	games.push_back("Tic Tac Toe");
	games.push_back("Connect 4");

	// add all of the supported engiens to the vector
	engines.push_back("Human");
	engines.push_back("Random Moves");
	engines.push_back("Naive Tree Search");

	// initialized all of the setting windows
	ticTacToeSettingsWindow = new GeneralSettingsWindow(new TicTacToeSettings());
	connect4SettingsWindow = new GeneralSettingsWindow(new Connect4Settings());
	for (int i = p1Index; i <= p2Index; i++) {
		randomMoveSettingsWindows[i] = new GeneralSettingsWindow(new RandomMoveSettings());
		naiveTreeSearchSettingsWindows[i] = new GeneralSettingsWindow(new NaiveTreeSearchSettings());
	}

	// set up all of the lists to let user select game and engines
	gameList = new QListWidget(this);
	gameList->setGeometry(QRect(QPoint(GAP_SIZE, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));
	p1List = new QListWidget(this);
	p1List->setGeometry(QRect(QPoint(GAP_SIZE*2 + ITEM_WIDTH, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));
	p2List = new QListWidget(this);
	p2List->setGeometry(QRect(QPoint(GAP_SIZE*3 + ITEM_WIDTH*2, GAP_SIZE), QSize(ITEM_WIDTH, LIST_HEIGHT)));

	// create the game settings button
	gameSettingsButton = new QPushButton("Game Settings", this);
	// set the location and size of the button
	QRect geom = QRect(QPoint(GAP_SIZE, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	gameSettingsButton->setGeometry(geom);
	// connect the button's signal to the handler
	connect(gameSettingsButton, SIGNAL (released()), this, SLOT (gameSettingsButtonHandler()));

	// create the engine1 settings button
	p1SettingsButton = new QPushButton("Player Settings", this);
	// set the location and size of the button
	geom = QRect(QPoint(GAP_SIZE*2 + ITEM_WIDTH, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	p1SettingsButton->setGeometry(geom);
	// connect the button's signal to the handler
	connect(p1SettingsButton, SIGNAL (released()), this, SLOT (p1SettingsButtonHandler()));

	// create the engine2s settings button
	p2SettingsButton = new QPushButton("Player Settings", this);
	// set the location and size of the button
	geom = QRect(QPoint(GAP_SIZE*3 + ITEM_WIDTH*2, GAP_SIZE*2 + LIST_HEIGHT), QSize(ITEM_WIDTH, BUTTON_HEIGHT));
	p2SettingsButton->setGeometry(geom);
	// connect the button's signal to the handler
	connect(p2SettingsButton, SIGNAL (released()), this, SLOT (p2SettingsButtonHandler()));

	// create the start button
	startGameButton = new QPushButton("Start Game", this);
	// set the location and size of the button
	geom = QRect(QPoint(GAP_SIZE, GAP_SIZE*3 + LIST_HEIGHT + BUTTON_HEIGHT), QSize(ITEM_WIDTH*3 + GAP_SIZE*2, BUTTON_HEIGHT));
	startGameButton->setGeometry(geom);
	// connect the button's signal to the handler
	connect(startGameButton, SIGNAL (released()), this, SLOT (startGameButtonHandler()));

	// loop through all of the games and add it to the list widget
	for (uint i = 0; i < games.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(games.at(i));
		gameList->addItem(listItem);
	}
	gameList->setCurrentRow(0);

	// loop through all of the engines and add it to the list widget
	for (uint i = 0; i < engines.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(engines.at(i));
		p1List->addItem(listItem);
	}
	p1List->setCurrentRow(0);

	// loop through all of the engines and add it to the list widget
	for (uint i = 0; i < engines.size(); i++) {
		QListWidgetItem* listItem = new QListWidgetItem;
		listItem->setText(engines.at(i));
		p2List->addItem(listItem);
	}
	p2List->setCurrentRow(0);

	// set the window size
	this->setFixedSize(GAP_SIZE*4 + ITEM_WIDTH*3, GAP_SIZE*4 + LIST_HEIGHT + BUTTON_HEIGHT*2);
}

void MainWindow::gameSettingsButtonHandler() {
	// look at what game was selected and open the settings window
	switch (gameList->currentRow()) {
	case 0:
		ticTacToeSettingsWindow->show(); break;
	case 1:
		connect4SettingsWindow->show(); break;
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
	// check to see if index is in range
	if (index < 0 || index >= 3) return;

	// grab what engine is selected
	int listIndex = (index == p1Index) ? p1List->currentRow() : p2List->currentRow();
	// open the settings window
	switch (listIndex) {
	case 1:
		randomMoveSettingsWindows[index]->updateAndShow(); break;
	case 2:
		naiveTreeSearchSettingsWindows[index]->updateAndShow(); break;
	default:
		cout << "breaking..." << endl; break;
	}
}

void MainWindow::startGameButtonHandler() {
	// create two new engines
	Engine* engines[2];
	// loop through the two players
	for (int i = 0; i < 2; i++) {
		// set the engine to the proper one selected, grabbing that player and engine's settings as well
		int index = (i == p1Index) ? p1List->currentRow() : p2List->currentRow();
		switch (index) {
		case 0:
			engines[i] = new HumanEngine; break;
		case 1:
			engines[i] = new RandomMoveEngine(*((RandomMoveSettings*)randomMoveSettingsWindows[i]->getSettings())); break;
		case 2:
			engines[i] = new NaiveTreeSearchEngine(*((NaiveTreeSearchSettings*)naiveTreeSearchSettingsWindows[i]->getSettings())); break;
		default:
			cout << "returning..." << endl; return;
		}
	}

	// look at what game is selected and start it up, passing in the engines
	if (gameList->currentRow() == 0) {
		TicTacToeSettings settings = *((TicTacToeSettings*)ticTacToeSettingsWindow->getSettings());
		TicTacToeGameWindow* window = new TicTacToeGameWindow(settings, engines[p1Index], engines[p2Index]);
		window->show();
	} else if (gameList->currentRow() == 1) {
		Connect4Settings settings = *((Connect4Settings*)connect4SettingsWindow->getSettings());
		Connect4GameWindow* window = new Connect4GameWindow(settings, engines[p1Index], engines[p2Index]);
		window->show();
	}
}


//*****************************************************************************
//Includes
#include "TicTacToeGameWindow.h"

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeSettings aSetting, Engine* engine1, Engine* engine2)
		: GameWindow(new TicTacToeGame(aSetting), engine1, engine2) {
	// initialize a signal mapper fro the buttons
	signalMapper = new QSignalMapper;
	// create a new game
	game = new TicTacToeGame(aSetting);
	// set the internal settings to those passed in
	settings = aSetting;
	// set the size equal to the square count
	int size = settings.get(squareCount);

	// create a QSize for the button size
	QSize buttonSize = QSize(settings.get(squareSize), settings.get(squareSize));
	// loop through all square locations
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			// create a new button
			QPushButton* button = new QPushButton("", this);
			// create a QPoint for the button location
			QPoint loc = QPoint((x+1)*settings.get(gapSize) + x*settings.get(squareSize),
					(y+1)*settings.get(gapSize) + y*settings.get(squareSize));
			// set the button's location and size
			button->setGeometry(QRect(loc, buttonSize));
			// add the button to the vector storing the game buttons
			buttons.push_back(button);

			// connect the button to the signal mapper, binding it to its id
			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*size);
		}
	}
	// connect the signal mapper to the button handler
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));
	// connect the move request signal and slot
	connect(this, SIGNAL (sendMoveRequest()), this, SLOT (recieveMoveRequest()), Qt::QueuedConnection);

	// set the window size and title
	QSize windowSize = QSize((size+1)*settings.get(gapSize) + size*settings.get(squareSize),
			(size+1)*settings.get(gapSize) + size*settings.get(squareSize));
	this->setFixedSize(windowSize);
	this->setWindowTitle("Tic Tac Toe");

	// send a move request to start the game
	emit sendMoveRequest();
}

void TicTacToeGameWindow::updateUI() {
	// loop through all square locations
	for (int y = 0; y < settings.get(squareCount); y++) {
		for (int x = 0; x < settings.get(squareCount); x++) {
			// create a variable for the id of the square we are on
			int id = x + y*settings.get(squareCount);
			// get the square's state
			int p = game->getSquare(id);
			// create a QString to hold what will be set to the button's text
			QString s = "";
			// change it if a player controls the square
			if (p == Game::player1) {
				s = PLAYER_1_CHAR;
			} else if (p == Game::player2) {
				s = PLAYER_2_CHAR;
			}
			// set the button text to the QString s
			buttons.at(id)->setText(s);
		}
	}
}


//*****************************************************************************
//Includes
#include "TicTacToeGameWindow.h"

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeSettings aSetting, Engine* engine1, Engine* engine2)
		: GameWindow(new TicTacToeGame(aSetting), engine1, engine2) {
	signalMapper = new QSignalMapper;
	game = new TicTacToeGame(aSetting);
	settings = aSetting;
	int size = settings.get(squareCount);

	QSize buttonSize = QSize(settings.get(squareSize), settings.get(squareSize));
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.get(gapSize) + x*settings.get(squareSize),
					(y+1)*settings.get(gapSize) + y*settings.get(squareSize));
			button->setGeometry(QRect(loc, buttonSize));
			buttons.push_back(button);

			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*size);
		}
	}
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));
	connect(this, SIGNAL (sendMoveRequest()), this, SLOT (recieveMoveRequest()), Qt::QueuedConnection);

	QSize windowSize = QSize((size+1)*settings.get(gapSize) + size*settings.get(squareSize),
			(size+1)*settings.get(gapSize) + size*settings.get(squareSize));
	this->setFixedSize(windowSize);
	this->setWindowTitle("Tic Tac Toe");

	emit sendMoveRequest();
}

void TicTacToeGameWindow::updateUI() {
	for (int y = 0; y < settings.get(squareCount); y++) {
		for (int x = 0; x < settings.get(squareCount); x++) {
			int id = x + y*settings.get(squareCount);
			int p = game->getSquare(id);
			cout << p;
			QString s = "";
			if (p == Game::player1) {
				s = PLAYER_1_CHAR;
			} else if (p == Game::player2) {
				s = PLAYER_2_CHAR;
			}
			buttons.at(id)->setText(s);
		}
	}
}


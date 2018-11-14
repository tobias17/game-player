//*****************************************************************************
//Includes
#include "TicTacToeGameWindow.h"

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeSettings_t aSetting) : QWidget(0) {
	signalMapper = new QSignalMapper;
	game = new TicTacToeGame(aSetting);
	settings = aSetting;
	int size = settings.squareCount;

	QSize buttonSize = QSize(settings.squareSize, settings.squareSize);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.gapSize + x*settings.squareSize, (y+1)*settings.gapSize + y*settings.squareSize);
			button->setGeometry(QRect(loc, buttonSize));
			buttons.push_back(button);

			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*size);
		}
	}
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	QSize windowSize = QSize((size+1)*settings.gapSize + size*settings.squareSize, (size+1)*settings.gapSize + size*settings.squareSize);
	this->setFixedSize(windowSize);
	this->setWindowTitle("Tic Tac Toe");
}


void TicTacToeGameWindow::boardButtonHandler(int id) {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn == TicTacToeGame::player1 && isPlayer1Human) {
		if (!game->makeMove(id, TicTacToeGame::player1)) return;
	} else if (playerTurn == TicTacToeGame::player2 && isPlayer2Human) {
		if (!game->makeMove(id, TicTacToeGame::player2)) return;
	} else {
		return;
	}
	QPushButton* b = buttons.at(id);
	b->setText((playerTurn == TicTacToeGame::player1) ? PLAYER_1_CHAR : PLAYER_2_CHAR);

	int winner = game->getWinner();
	if (winner != TicTacToeGame::none) {
		if (winner == TicTacToeGame::player1) {
			messageBox->setText("Player 1 has won the game!");
		} else if (winner == TicTacToeGame::player2) {
			messageBox->setText("Player 2 has won the game!");
		} else {
			messageBox->setText("The game has ended in a tie.");
		}
		messageBox->exec();
	}
}

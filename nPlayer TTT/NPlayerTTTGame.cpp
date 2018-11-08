//*****************************************************************************
//Includes
#include "NPlayerTTTGame.h"

NPlayerTTTGame::NPlayerTTTGame(NPlayerTTTSettings_t aSetting) : QWidget(0) {
	signalMapper = new QSignalMapper;
	settings = aSetting;
	int size = settings.squareCount;
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	QSize buttonSize = QSize(settings.squareSize, settings.squareSize);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.gapSize + x*settings.squareSize, (y+1)*settings.gapSize + y*settings.squareSize);
			button->setGeometry(QRect(loc, buttonSize));
			buttons.push_back(button);

			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*size);
			board[x][y] = none;
		}
	}
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	QSize windowSize = QSize((size+1)*settings.gapSize + size*settings.squareSize, (size+1)*settings.gapSize + size*settings.squareSize);
	this->setFixedSize(windowSize);
	this->setWindowTitle("Tic Tac Toe");
}

void NPlayerTTTGame::makeMove(int id, int player) {
	if (player != playerTurn) return;

	board[id%settings.squareCount][id/settings.squareCount] = player;

	QString s;
	if (player == player1) {
		s = PLAYER_1_CHAR;
	} else if (player == player2) {
		s = PLAYER_2_CHAR;
	} else {
		return;
	}
	QPushButton* b = buttons.at(id);
	b->setText(s);

	int winner = getWinner();
	if (winner != none) {
		if (winner == player1) {
			messageBox->setText("Player 1 has won the game!");
		} else if (winner == player2) {
			messageBox->setText("Player 2 has won the game!");
		} else {
			messageBox->setText("The game has ended in a tie.");
		}
		playerTurn = none;
		messageBox->show();
	}

	if (playerTurn == player1) {
		playerTurn = player2;
	} else if (playerTurn == player2) {
		playerTurn = player1;
	}
}

void NPlayerTTTGame::boardButtonHandler(int id) {

	if (playerTurn == player1 && isPlayer1Human) {
		makeMove(id, player1);
	} else if (playerTurn == player2 && isPlayer2Human) {
		makeMove(id, player2);
	}
}

int NPlayerTTTGame::getWinner() {
	int size = settings.squareCount;
	QPoint dirs[4] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1) };
	bool hasAnEmpty = false;

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			for (int i = 0; i < 4; i++) {
				if (board[x][y] == none) hasAnEmpty = true;
				QPoint dir = dirs[i];
				int dx = 0;
				int dy = 0;
				int player = board[x][y];
				int streak = 1;
				while (true) {
					dx += dir.x();
					dy += dir.y();
					if (x+dx < 0 || x+dx >= size || y+dy < 0 || y+dy >= size) {
						break;
					}
					if (board[x+dx][y+dy] == player) {
						streak++;
						if (player != none && streak == settings.squaresToWin) {
							return player;
						}
					} else {
						player = board[x+dx][y+dy];
						streak = 1;
					}
				}
			}
		}
	}
	if (!hasAnEmpty) return tie;
	return none;
}

//int TicTacToeGame::getWinner() {
//	return none;
//}




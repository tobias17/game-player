//*****************************************************************************
//Includes
#include "Connect4Game.h"

Connect4Game::Connect4Game(Connect4Settings_t aSetting) {
	settings = aSetting;
	board = new int*[settings.width*settings.height];
	for (int x = 0; x < settings.width; x++) board[x] = new int[settings.height];

	for (int y = 0; y < settings.height; y++) {
		for (int x = 0; x < settings.width; x++) {
			board[x][y] = Game::none;
		}
	}
}

Game* Connect4Game::copy() {
	Connect4Game* newGame = new Connect4Game(settings);
	newGame->setBoard(board);
	newGame->setPlayerTurn(playerTurn);
	return (Game*) newGame;
}

void Connect4Game::setBoard(int** aBoard) {
	board = new int*[settings.width];
	for (int x = 0; x < settings.width; x++) board[x] = new int[settings.height];

	for (int y = 0; y < settings.height; y++) {
		for (int x = 0; x < settings.width; x++) {
			board[x][y] = aBoard[x][y];
		}
	}
}

bool Connect4Game::makeMove(int id, int player) {
	if (player != playerTurn) return false;

	int x = id % settings.width;
	if (board[x][0] != Game::none) return false;

	for (int y = settings.height - 1; y >= 0; y--) {
		if (board[x][y] == Game::none) {
			board[x][y] = player;
			break;
		}
	}

	if (playerTurn == Game::player1) {
		playerTurn = Game::player2;
	} else if (playerTurn == Game::player2) {
		playerTurn = Game::player1;
	}

	if (getWinner() != Game::none) {
		playerTurn = Game::none;
	}

	return true;
}

int Connect4Game::getWinner() {
	QPoint dirs[4] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1) };
	bool hasAnEmpty = false;

	for (int x = 0; x < settings.width; x++) {
		for (int y = 0; y < settings.width; y++) {
			for (int i = 0; i < 4; i++) {
				if (board[x][y] == Game::none) hasAnEmpty = true;
				QPoint dir = dirs[i];
				int dx = 0;
				int dy = 0;
				int player = board[x][y];
				int streak = 1;
				while (true) {
					dx += dir.x();
					dy += dir.y();
					if (x+dx < 0 || x+dx >= settings.width || y+dy < 0 || y+dy >= settings.height) {
						break;
					}
					if (board[x+dx][y+dy] == player) {
						streak++;
						if (player != Game::none && streak == settings.squaresToWin) {
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
	return Game::none;
}

vector<int> Connect4Game::getPossibleMoves() {
	vector<int> v;
	for (int x = 0; x < settings.width; x++) {
		if (board[x][0] == Game::none) {
			v.push_back(x);
		}
	}
	return v;
}

void Connect4Game::dispBoard() {
	for (int y = 0; y < settings.height; y++) {
		for (int x = 0; x < settings.width; x++) {
			cout << ((board[x][y] == 0) ? "-" : (board[x][y] == 1) ? "X" : "O");
		}
		cout << endl;
	}
}


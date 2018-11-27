//*****************************************************************************
//Includes
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(TicTacToeSettings aSetting) {
	settings = aSetting;
	int size = settings.get(squareCount);
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = Game::none;
		}
	}
}

Game* TicTacToeGame::copy() {
	TicTacToeGame* newGame = new TicTacToeGame(settings);
	newGame->setBoard(board);
	newGame->setPlayerTurn(playerTurn);
	return (Game*) newGame;
}

void TicTacToeGame::setBoard(int** aBoard) {
	int size = settings.get(squareCount);
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = aBoard[x][y];
		}
	}
}

bool TicTacToeGame::makeMove(int id, int player) {
	return makeMove(id%settings.get(squareCount), id/settings.get(squareCount), player);
}

bool TicTacToeGame::makeMove(int x, int y, int player) {
	if (player != playerTurn) return false;
	if (board[x][y] != Game::none) return false;

	board[x][y] = player;

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

int TicTacToeGame::getWinner() {
	int size = settings.get(squareCount);
	QPoint dirs[4] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1) };
	bool hasAnEmpty = false;

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
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
					if (x+dx < 0 || x+dx >= size || y+dy < 0 || y+dy >= size) {
						break;
					}
					if (board[x+dx][y+dy] == player) {
						streak++;
						if (player != Game::none && streak == settings.get(squaresToWin)) {
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

vector<int> TicTacToeGame::getPossibleMoves() {
	int size = settings.get(squareCount);
	vector<int> v;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (board[x][y] == Game::none) {
				v.push_back(x + y*size);
			}
		}
	}
	return v;
}

void TicTacToeGame::dispBoard() {
	int size = settings.get(squareCount);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			cout << ((board[x][y] == 0) ? "-" : (board[x][y] == 1) ? "X" : "O");
		}
		cout << endl;
	}
}


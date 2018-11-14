//*****************************************************************************
//Includes
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(TicTacToeSettings_t aSetting) {
	settings = aSetting;
	int size = settings.squareCount;
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = none;
		}
	}
}

bool TicTacToeGame::makeMove(int id, int player) {
	return makeMove(id%settings.squareCount, id/settings.squareCount, player);
}

bool TicTacToeGame::makeMove(int x, int y, int player) {
	if (player != playerTurn) return false;

	board[x][y] = player;

	if (playerTurn == player1) {
		playerTurn = player2;
	} else if (playerTurn == player2) {
		playerTurn = player1;
	}
	return true;
}

int TicTacToeGame::getWinner() {
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

vector<int> TicTacToeGame::getPossibleMoves() {
	vector<int> v;
	return v;
}

//int TicTacToeGame::getWinner() {
//	return none;
//}




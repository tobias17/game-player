//*****************************************************************************
//Includes
#include "Connect4Game.h"

Connect4Game::Connect4Game(Connect4Settings aSetting) {
	// set the internal settings to those passed in
	settings = aSetting;

	// create a new board
	board = new int*[settings.get(itemWidth)];
	for (int x = 0; x < settings.get(itemWidth); x++){
		board[x] = new int[settings.get(itemHeight)];
	}

	// initialize the board to be blank
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			board[x][y] = Game::none;
		}
	}
}

Connect4Game::Connect4Game(Connect4Game* aGame) {
	// set the internal settings and player turn to the passed in game's
	settings = aGame->getSettings();
	playerTurn = aGame->getPlayerTurn();

	// create a new board
	board = new int*[settings.get(itemWidth)];
	for (int x = 0; x < settings.get(itemWidth); x++){
		board[x] = new int[settings.get(itemHeight)];
	}

	// initialize the board to be what the game passed in's is
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			board[x][y] = aGame->getSquare(x, y);
		}
	}
}

Connect4Game::~Connect4Game() {
	// loop through the board and delete each row
	for (int i = 0; i < settings.get(itemWidth); i++) {
		delete[] board[i];
	}
	// delete the board
	delete[] board;
}

Game* Connect4Game::copy() {
	// return a new game initialized to this one
	return (Game*) new Connect4Game(this);
}

void Connect4Game::setBoard(int** aBoard) {
	// create a new board
	board = new int*[settings.get(itemWidth)];
	for (int x = 0; x < settings.get(itemWidth); x++) board[x] = new int[settings.get(itemHeight)];

	// loop through all locations on the new board
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			// set the value of the new board to the passed in board
			board[x][y] = aBoard[x][y];
		}
	}
}

bool Connect4Game::makeMove(int id, int player) {
	// check to see if the right player is making the move
	if (player != playerTurn) return false;

	// check to see if the move is legal
	int x = id % settings.get(itemWidth);
	if (board[x][0] != Game::none) return false;

	// make the move
	for (int y = settings.get(itemHeight) - 1; y >= 0; y--) {
		if (board[x][y] == Game::none) {
			board[x][y] = player;
			prevMoveX = x;
			prevMoveY = y;
			prevMovePlayer = player;
			break;
		}
	}

	// toggle the player turn
	if (playerTurn == Game::player1) {
		playerTurn = Game::player2;
	} else if (playerTurn == Game::player2) {
		playerTurn = Game::player1;
	}

	// check to see if the game is over
	if (getWinner() != Game::none) {
		// if so, set player turn to none to set the game as over
		playerTurn = Game::none;
	}

	// return true to tell the caller that the move was actually made
	return true;
}

int Connect4Game::getWinnerPrevMove() {

	/*
	 * This algorithm only checks the squares surrounding
	 * where the last move was made on the board. It goes
	 * in all directions until it no longer sees a square
	 * from the player that just made the move. If it sees
	 * a streak long enough to win, it will return that.
	 */

	// vertical
	int streak = 1;
	for (int y = prevMoveY + 1; y < settings.get(itemHeight); y++) {
		if (board[prevMoveX][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}
	for (int y = prevMoveY - 1; y >= 0; y--) {
		if (board[prevMoveX][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}

	// horizontal
	streak = 1;
	for (int x = prevMoveX + 1; x < settings.get(itemWidth); x++) {
		if (board[x][prevMoveY] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}
	for (int x = prevMoveX - 1; x >= 0; x--) {
		if (board[x][prevMoveY] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}

	// diagonal tl to br
	streak = 1;
	int x = prevMoveX + 1;
	for (int y = prevMoveY + 1; x < settings.get(itemWidth) && y < settings.get(itemHeight); x++, y++) {
		if (board[x][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}
	x = prevMoveX - 1;
	for (int y = prevMoveY - 1; x >= 0 && y >= 0; x--, y--) {
		if (board[x][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}

	// diagonal tr to bl
	streak = 1;
	x = prevMoveX + 1;
	for (int y = prevMoveY - 1; x < settings.get(itemWidth) && y >= 0; x++, y--) {
		if (board[x][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}
	x = prevMoveX - 1;
	for (int y = prevMoveY + 1; x >= 0 && y < settings.get(itemHeight); x--, y++) {
		if (board[x][y] == prevMovePlayer) {
			streak++;
			if (streak >= settings.get(squaresToWin)) {
				return prevMovePlayer;
			}
		} else {
			break;
		}
	}

	// loop through the top row and if spaces are available, return no winner
	for (int x = 0; x < settings.get(itemWidth); x++) {
		if (board[x][0] == Game::none) {
			return Game::none;
		}
	}
	// if there are no spaces left to move to, return that the game ended in tied
	return Game::tie;
}

int Connect4Game::getWinner() {

	// if there was a previous move, run the more efficient check
	if (prevMoveX >= 0 && prevMoveY >= 0) {
		return getWinnerPrevMove();
	}

	// create and initialize variable to be used
	int player = Game::none;
	int streak = 0;

	/*
	 * Each loop runs through a set of lines and
	 * keeps track of how many in a row it has seen.
	 * Once it reaches how many are needed to win,
	 * it will return what player just won.
	 */

	// vertical checks
	for (int x = 0; x < settings.get(itemWidth); x++) {
		player = Game::none;
		streak = 0;
		for (int y = 0; y < settings.get(itemHeight); y++) {
			if (board[x][y] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x][y];
				streak = 1;
			}
		}
	}

	// horizontal checks
	for (int y = 0; y < settings.get(itemHeight); y++) {
		player = Game::none;
		streak = 0;
		for (int x = 0; x < settings.get(itemWidth); x++) {
			if (board[x][y] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x][y];
				streak = 1;
			}
		}
	}

	// diagonal checks tl to br left wall
	for (int y = 0; y < settings.get(itemHeight) - settings.get(squaresToWin) + 1; y++) {
		player = Game::none;
		streak = 0;
		int dy = 0;
		for (int x = 0; x < settings.get(itemWidth); x++, dy++) {
			if (board[x][y+dy] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x][y+dy];
				streak = 1;
			}
		}
	}

	// diagonal checks tr to bl right wall
	for (int y = 0; y < settings.get(itemHeight) - settings.get(squaresToWin) + 1; y++) {
		player = Game::none;
		streak = 0;
		int dy = 0;
		for (int x = settings.get(itemWidth)-1; x >= 0; x--, dy++) {
			if (board[x][y+dy] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x][y+dy];
				streak = 1;
			}
		}
	}

	// diagonal checks tl to br top wall
	for (int x = 1; x < settings.get(itemWidth) - settings.get(squaresToWin) + 1; x++) {
		player = Game::none;
		streak = 0;
		int dx = 0;
		for (int y = 0; y < settings.get(itemHeight) && x+dx < settings.get(itemWidth); y++, dx++) {
			if (board[x+dx][y] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x+dx][y];
				streak = 1;
			}
		}
	}

	// diagonal checks tr to bl top wall
	for (int x = settings.get(itemWidth) - 2; x >= settings.get(squaresToWin) - 1; x--) {
		player = Game::none;
		streak = 0;
		int dx = 0;
		for (int y = 0; y < settings.get(itemHeight) && x+dx >= 0; y++, dx--) {
			if (board[x+dx][y] == player) {
				streak++;
				if (player != Game::none && streak == settings.get(squaresToWin)) {
					return player;
				}
			} else {
				player = board[x+dx][y];
				streak = 1;
			}
		}
	}

	// loop through the top row and if spaces are available, return no winner
	for (int x = 0; x < settings.get(itemWidth); x++) {
		if (board[x][0] == Game::none) {
			return Game::none;
		}
	}
	// if there are no spaces left to move to, return that the game ended in tied
	return Game::tie;
}

vector<int> Connect4Game::getPossibleMoves() {
	// declare a vector to store the possible moves
	vector<int> v;
	// go along the top row
	for (int x = 0; x < settings.get(itemWidth); x++) {
		// if the top of the column is blank, add it as a possible move
		if (board[x][0] == Game::none) {
			v.push_back(x);
		}
	}
	// return the possible moves vector
	return v;
}

void Connect4Game::dispBoard() {
	// loop through all squares and output the values - used for debug only
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			cout << ((board[x][y] == 0) ? " -" : (board[x][y] == 1) ? " X" : " O");
		}
		cout << endl;
	}
}


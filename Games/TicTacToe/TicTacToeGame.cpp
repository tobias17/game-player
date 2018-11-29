//*****************************************************************************
//Includes
#include "TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(TicTacToeSettings aSetting) {
	// set the internal settings to the passed in one
	settings = aSetting;
	// set the size equal to the square count
	int size = settings.get(squareCount);

	// create a new game board
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	// initialize the game board to be blank
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = Game::none;
		}
	}
}

TicTacToeGame::TicTacToeGame(TicTacToeGame* aGame) {
	// set the internal settings and player turn to the passed in game's
	settings = aGame->getSettings();
	playerTurn = aGame->getPlayerTurn();
	// set the size equal to the square count
	int size = settings.get(squareCount);

	// create a new game board
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	// initialize the board to be what the game passed in's is
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = aGame->getSquare(x, y);
		}
	}
}

TicTacToeGame::~TicTacToeGame() {
	// loop through all rows and delete them
	for (int i = 0; i < settings.get(squareCount); i++) {
		delete[] board[i];
	}
	// delete the board itself
	delete[] board;
}

Game* TicTacToeGame::copy() {
	// create a new board and return it
	return (Game*) new TicTacToeGame(this);
}

void TicTacToeGame::setBoard(int** aBoard) {
	// set the size equal to the square count
	int size = settings.get(squareCount);

	// create a new board
	board = new int*[size];
	for (int x = 0; x < size; x++) board[x] = new int[size];

	// loop through all squares and set new board to other board
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			board[x][y] = aBoard[x][y];
		}
	}
}

bool TicTacToeGame::makeMove(int id, int player) {
	// sends the move to other function converted to x, y coordinates
	return makeMove(id%settings.get(squareCount), id/settings.get(squareCount), player);
}

bool TicTacToeGame::makeMove(int x, int y, int player) {
	// check to see if the right player is making the move
	if (player != playerTurn) return false;
	// check to see if the spot on the board is empty
	if (board[x][y] != Game::none) return false;

	// make the move
	board[x][y] = player;

	// toggle the player turn
	if (playerTurn == Game::player1) {
		playerTurn = Game::player2;
	} else if (playerTurn == Game::player2) {
		playerTurn = Game::player1;
	}

	// check for a winner
	if (getWinner() != Game::none) {
		// if there is a winner, set the player turn to none to stop game
		playerTurn = Game::none;
	}

	// return true at end to tell caller that move worked
	return true;
}

int TicTacToeGame::getWinner() {
	// set the size equal to the square count
	int size = settings.get(squareCount);
	// create an array for the 4 possible directions to scan
	QPoint dirs[4] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1) };
	// create a boolean to check for empty spaces to tell if the game ended in tie
	bool hasAnEmpty = false;

	// loop through all location on the board
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			// loop through all 4 directions to scan
			for (int i = 0; i < 4; i++) {
				// check to see if the board is empty
				if (board[x][y] == Game::none) hasAnEmpty = true;
				// set the current direction to a variable
				QPoint dir = dirs[i];
				// initialize variables
				int dx = 0;
				int dy = 0;
				int player = board[x][y];
				int streak = 1;
				// loop until break
				while (true) {
					// increment the direction modifier integers
					dx += dir.x();
					dy += dir.y();
					// check to see if we are still in the game board
					if (x+dx < 0 || x+dx >= size || y+dy < 0 || y+dy >= size) {
						break;
					}
					// check to see if the square is the same as the previous
					if (board[x+dx][y+dy] == player) {
						// increment the streak
						streak++;
						// check to see if streak is enough to win
						if (player != Game::none && streak == settings.get(squaresToWin)) {
							// if so return the player that won
							return player;
						}
					} else {
						// otherwise reset the streak and set the streak player
						player = board[x+dx][y+dy];
						streak = 1;
					}
				}
			}
		}
	}
	// if the board does not have an empty tile return a tie
	if (!hasAnEmpty) return tie;
	// else return that there is no winner
	return Game::none;
}

vector<int> TicTacToeGame::getPossibleMoves() {
	// set size equal to square count
	int size = settings.get(squareCount);
	// create a vector v to hold the possible move
	vector<int> v;
	// loop through all squares on the board
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			// check to see if the square is empty
			if (board[x][y] == Game::none) {
				// if empty, add it to possible moves
				v.push_back(x + y*size);
			}
		}
	}
	// return the vector of possible moves
	return v;
}

void TicTacToeGame::dispBoard() {
	// loop through all squares and output the values - used for debug only
	int size = settings.get(squareCount);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			cout << ((board[x][y] == 0) ? "-" : (board[x][y] == 1) ? "X" : "O");
		}
		cout << endl;
	}
}


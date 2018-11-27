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

Game* Connect4Game::copy() {
	// create a new Connect 4 game
	Connect4Game* newGame = new Connect4Game(settings);
	// set the new game's board to this board
	newGame->setBoard(board);
	// set the new game's player turn to this game's
	newGame->setPlayerTurn(playerTurn);
	// return the Connect 4 game
	return (Game*) newGame;
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

int Connect4Game::getWinner() {
	// create an array for the 4 possible directions to scan
	QPoint dirs[4] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1) };
	// create a boolean to check for empty spaces to tell if the game ended in tie
	bool hasAnEmpty = false;

	// loop through all location on the board
	for (int x = 0; x < settings.get(itemWidth); x++) {
		for (int y = 0; y < settings.get(itemWidth); y++) {
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
					if (x+dx < 0 || x+dx >= settings.get(itemWidth)
							|| y+dy < 0 || y+dy >= settings.get(itemHeight)) {
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
			cout << ((board[x][y] == 0) ? "-" : (board[x][y] == 1) ? "X" : "O");
		}
		cout << endl;
	}
}


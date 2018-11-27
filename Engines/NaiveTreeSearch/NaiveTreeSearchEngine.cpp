//*****************************************************************************
//Includes
#include <chrono>
#include "NaiveTreeSearchEngine.h"

NaiveTreeSearchEngine::NaiveTreeSearchEngine(NaiveTreeSearchSettings aSetting) {
	// set the internal settings to those passed in
	settings = aSetting;
}

int NaiveTreeSearchEngine::getMove(Game* game) {
	// ask the game for all possible moves and store it in a vector v
	vector<int> v = game->getPossibleMoves();
	// create an array to store how good each possible move is
	int weights[v.size()];
	// initialize the array of weights to 0
	for (uint i = 0; i < v.size(); i++) weights[i] = 0;

	// store the current time so the engine only calculates for the time it is allowed
	auto start = chrono::steady_clock::now();
	// loop for the permitted time
	while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < settings.get(timePerMove_ms)) {
		// loop through all of the possible starting moves
		for (uint start = 0; start < v.size(); start++) {
			// check to see if we were terminated
			if (!isRunning()) return v.at(0);

			// create a new game
			Game* newGame = game->copy();
			// make our starting move
			newGame->makeMove(v.at(start), newGame->getPlayerTurn());

			// loop until the game is over
			while (newGame->getWinner() == Game::none) {
				// grab all possible moves
				vector<int> newMoves = newGame->getPossibleMoves();
				// make a random move based on what is possible
				newGame->makeMove(newMoves.at(rand() % newMoves.size()), newGame->getPlayerTurn());
			}
			if (newGame->getWinner() == game->getPlayerTurn()) {
				// if the engine won the game, increment the weight for the starting move
				weights[start]++;
			} else if (newGame->getWinner() == Game::otherPlayer(game->getPlayerTurn())) {
				// if the engine lost the game, decrement the weight for the starting move
				weights[start]--;
			}
		}
	}
	// initialize variables to find best weight
	int best = weights[0];
	int bestMove = v.at(0);
	// loop through all starting locations
	for (uint i = 1; i < v.size(); i++) {
		// check to see if there is a better weight
		if (weights[i] > best) {
			// store the better weight
			best = weights[i];
			bestMove = v.at(i);
		}
	}
	// return the move with the highest weight
	return bestMove;
}

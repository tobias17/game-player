//*****************************************************************************
//Includes
#include <unistd.h>
#include "RandomMoveEngine.h"

RandomMoveEngine::RandomMoveEngine(RandomMoveSettings aSetting) {
	// set the internal settings to those passed in
	settings = aSetting;
}

int RandomMoveEngine::getMove(Game* game) {
	// ask the game for all possible moves and set it to a vector v
	vector<int> v = game->getPossibleMoves();
	// loop through all the milliseconds that are requested to be waited
	for (int i = 0; i < settings.get(moveDelay_ms); i++) {
		// sleep for a millisecond
		usleep(1000);
		// the function sleeps in chunks to check if it needs to break out
		if (!isRunning()) return v.at(0);
	}
	// return a random move
	return v.at(rand() % v.size());
}

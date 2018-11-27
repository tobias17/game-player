//*****************************************************************************
//Includes
#include <unistd.h>
#include "RandomMoveEngine.h"

RandomMoveEngine::RandomMoveEngine(RandomMoveEngineSettings_t aSetting) {
	settings = aSetting;
}

int RandomMoveEngine::getMove(Game* game) {
	vector<int> v = game->getPossibleMoves();
	for (int i = 0; i < settings.moveDelay_ms; i++) {
		usleep(1000);
		if (!isRunning()) return v.at(0);
	}
	int i = rand() % v.size();
	return v.at(i);
}

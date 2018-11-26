//*****************************************************************************
//Includes
#include "RandomMoveEngine.h"

RandomMoveEngine::RandomMoveEngine(RandomMoveEngineSettings_t aSetting) {
	settings = aSetting;
}

int RandomMoveEngine::getMove(Game* game) {
	usleep(settings.moveDelay_ms * 1000);
	vector<int> v = game->getPossibleMoves();
	int i = rand() % v.size();
	return v.at(i);
}

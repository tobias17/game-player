#ifndef RANDOM_MOVE_ENGINE_H_
#define RANDOM_MOVE_ENGINE_H_

//*****************************************************************************
//Includes
#include "../Engine.h"
#include "RandomMoveEngineSettings.h"

class RandomMoveEngine : public Engine {
public:
	RandomMoveEngine(RandomMoveEngineSettings_t);
	int getMove(Game*);
private:
	RandomMoveEngineSettings_t settings;
};

#endif /* RANDOM_MOVE_ENGINE_H_ */

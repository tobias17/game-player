#ifndef RANDOM_MOVE_ENGINE_H_
#define RANDOM_MOVE_ENGINE_H_

//*****************************************************************************
//Includes
#include "../Engine.h"
#include "RandomMoveSettings.h"

class RandomMoveEngine : public Engine {
public:
	RandomMoveEngine(RandomMoveSettings);
	int getMove(Game*);
private:
	RandomMoveSettings settings;
};

#endif /* RANDOM_MOVE_ENGINE_H_ */

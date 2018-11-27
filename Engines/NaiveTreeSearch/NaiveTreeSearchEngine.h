#ifndef NAIVE_TREE_SEARCH_ENGINE_H_
#define NAIVE_TREE_SEARCH_ENGINE_H_

//*****************************************************************************
//Includes
#include <unistd.h>
#include "../Engine.h"
#include "NaiveTreeSearchSettings.h"

class NaiveTreeSearchEngine : public Engine {
public:
	NaiveTreeSearchEngine(NaiveTreeSearchSettings aSetting);
	int getMove(Game* aGame);
private:
	NaiveTreeSearchSettings settings;
};

#endif /* NAIVE_TREE_SEARCH_ENGINE_H_ */

#ifndef NAIVE_TREE_SEARCH_ENGINE_H_
#define NAIVE_TREE_SEARCH_ENGINE_H_

//*****************************************************************************
//Includes
#include <unistd.h>
#include "../Engine.h"
#include "NaiveTreeSearchEngineSettings.h"

class NaiveTreeSearchEngine : public Engine {
public:
	NaiveTreeSearchEngine(NaiveTreeSearchEngineSettings_t);
	int getMove(Game*);
private:
	NaiveTreeSearchEngineSettings_t settings;
};

#endif /* NAIVE_TREE_SEARCH_ENGINE_H_ */

#ifndef GAME_H_
#define GAME_H_

//*****************************************************************************
//Includes
#include <vector>

using namespace std;

class Game {
public:
	virtual ~Game() {};
	virtual vector<int> getPossibleMoves() = 0;
};

#endif /* GAME_H_ */

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
	virtual Game* copy() = 0;
	virtual bool makeMove(int, int) = 0;
	virtual int getWinner() = 0;
	virtual int getPlayerTurn() { return playerTurn; };
	enum Players { none, player1, player2, tie };
	static int otherPlayer(int player) { if (player == player1) return player2; return player1; };
protected:
	int playerTurn = player1;
};

#endif /* GAME_H_ */

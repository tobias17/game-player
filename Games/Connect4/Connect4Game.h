#ifndef CONNECT_4_GAME_H_
#define CONNECT_4_GAME_H_

//*****************************************************************************
//Includes
#include "../Game.h"
#include "Connect4Settings.h"

using namespace std;

class Connect4Game : public Game {
public:
	Connect4Game(Connect4Settings);
	int getWinner();
	bool makeMove(int id, int player);
	vector<int> getPossibleMoves();
	Game* copy();
	void setBoard(int** aBoard);
	void setPlayerTurn(int aPlayerTurn) { playerTurn = aPlayerTurn; };
	int getSquare(int id) { return board[id%settings.get(itemWidth)][id/settings.get(itemWidth)]; };
	Connect4Settings getSettings() { return settings; };
	void dispBoard();
private:
	Connect4Settings settings;
	int** board;
};

#endif /* CONNECT_4_GAME_H_ */

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
	Connect4Game(Connect4Game*);
	~Connect4Game();
	int getWinner();
	int getWinner2();
	int getWinnerPrevMove();
	bool makeMove(int id, int player);
	vector<int> getPossibleMoves();
	Game* copy();
	void setBoard(int** aBoard);
	void setPlayerTurn(int aPlayerTurn) { playerTurn = aPlayerTurn; };
	int getSquare(int id) { return board[id%settings.get(itemWidth)][id/settings.get(itemWidth)]; };
	int getSquare(int x, int y) { return board[x][y]; };
	Connect4Settings getSettings() { return settings; };
	void dispBoard();
private:
	Connect4Settings settings;
	int** board;
	int prevMoveX = -1;
	int prevMoveY = -1;
	int prevMovePlayer = Game::none;
};

#endif /* CONNECT_4_GAME_H_ */

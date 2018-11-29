#ifndef TIC_TAC_TOE_GAME_H_
#define TIC_TAC_TOE_GAME_H_

//*****************************************************************************
//Includes
#include "TicTacToeSettings.h"
#include "../Game.h"

using namespace std;

class TicTacToeGame : public Game {
public:
	TicTacToeGame(TicTacToeSettings);
	TicTacToeGame(TicTacToeGame*);
	~TicTacToeGame();
	int getWinner();
	bool makeMove(int id, int player);
	bool makeMove(int x, int y, int player);
	vector<int> getPossibleMoves();
	Game* copy();
	void setBoard(int** aBoard);
	void setPlayerTurn(int aPlayerTurn) { playerTurn = aPlayerTurn; };
	int getSquare(int id) { return board[id%settings.get(squareCount)][id/settings.get(squareCount)]; };
	int getSquare(int x, int y) { return board[x][y]; };
	TicTacToeSettings getSettings() { return settings; };
	void dispBoard();
private:
	TicTacToeSettings settings;
	int** board;
};

#endif /* TIC_TAC_TOE_GAME_H_ */

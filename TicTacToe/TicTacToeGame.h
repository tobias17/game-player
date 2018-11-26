//*****************************************************************************
//Includes
#include "TicTacToeSettings.h"
#include "../Game.h"

using namespace std;

class TicTacToeGame : public Game {
public:
	TicTacToeGame(TicTacToeSettings_t);
	int getWinner();
	bool makeMove(int id, int player);
	bool makeMove(int x, int y, int player);
	vector<int> getPossibleMoves();
	Game* copy();
	void setBoard(int** aBoard);
	void setPlayerTurn(int aPlayerTurn) { playerTurn = aPlayerTurn; };
	int getSquare(int x, int y) { return board[x][y]; };
	TicTacToeSettings_t getSettings() { return settings; };
	void dispBoard();
private:
	TicTacToeSettings_t settings;
	int** board;
};

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
	int getPlayerTurn() { return playerTurn; };
	int getSquare(int x, int y) { return board[x][y]; };
	TicTacToeSettings_t getSettings() { return settings; };
	enum Players { none, player1, player2, tie };
private:
	int playerTurn = player1;
	TicTacToeSettings_t settings;
	int** board;
};

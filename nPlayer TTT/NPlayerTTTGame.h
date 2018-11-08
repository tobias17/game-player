//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>

#include "NPlayerTTTSettings.h"

#define PLAYER_1_CHAR	"X"
#define PLAYER_2_CHAR	"O"

using namespace std;

class NPlayerTTTGame : public QWidget {
	Q_OBJECT
public:
//	TicTacToeGame();
	NPlayerTTTGame(NPlayerTTTSettings_t);
private slots:
	void boardButtonHandler(int id);
private:
	int getWinner();
	void makeMove(int id, int player);
	QSignalMapper* signalMapper;
	enum Players { none, player1, player2, tie };
	int playerTurn = player1;
	bool isPlayer1Human = true;
	bool isPlayer2Human = true;
	NPlayerTTTSettings_t settings;
	vector<QPushButton*> buttons;
	QMessageBox* messageBox;
	int** board;
};

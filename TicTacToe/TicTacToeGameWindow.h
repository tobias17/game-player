//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>
#include "TicTacToeGame.h"

#define PLAYER_1_CHAR	"X"
#define PLAYER_2_CHAR	"O"

class TicTacToeGameWindow : public QWidget {
	Q_OBJECT
public:
	TicTacToeGameWindow(TicTacToeSettings_t);
private slots:
	void boardButtonHandler(int id);
private:
	QSignalMapper* signalMapper;
	TicTacToeGame* game;
	vector<QPushButton*> buttons;
	QMessageBox* messageBox;
	bool isPlayer1Human = true;
	bool isPlayer2Human = true;
	TicTacToeSettings_t settings;
};

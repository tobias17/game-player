#ifndef TIC_TAC_TOE_GAME_WINDOW_H_
#define TIC_TAC_TOE_GAME_WINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>
#include <QThread>
#include "TicTacToeGame.h"
#include "../../Engines/RandomMoveEngine/RandomMoveEngine.h"
#include "../GameWindow.h"

#define PLAYER_1_CHAR	"X"
#define PLAYER_2_CHAR	"O"

class TicTacToeGameWindow : public GameWindow {
	Q_OBJECT
public:
	TicTacToeGameWindow(TicTacToeSettings, Engine*, Engine*);
	~TicTacToeGameWindow() {};
	void setEngine(Engine*, int player);
	enum EngineHandlerIndecies { p1Engine, p2Engine };
private:
	void updateUI();
//	void checkForWinner();
	QSignalMapper* signalMapper;
//	TicTacToeGame* game;
	TicTacToeSettings settings;
};

#endif /* TIC_TAC_TOE_GAME_WINDOW_H_ */

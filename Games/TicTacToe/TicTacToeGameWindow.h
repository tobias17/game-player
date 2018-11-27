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
	TicTacToeGameWindow(TicTacToeSettings_t, Engine*, Engine*);
	~TicTacToeGameWindow() {};
	void setEngine(Engine*, int player);
	enum EngineHandlerIndecies { p1Engine, p2Engine };
signals:
	void sendMoveRequest();
	void sendP1EngineMove(Game*);
	void sendP2EngineMove(Game*);
private slots:
	void boardButtonHandler(int id);
	void recieveMoveRequest();
	void receiveP1EngineMove(int id);
	void receiveP2EngineMove(int id);
private:
	void updateUI();
	void checkForWinner();
	QSignalMapper* signalMapper;
	TicTacToeGame* game;
	TicTacToeSettings_t settings;
};

#endif /* TIC_TAC_TOE_GAME_WINDOW_H_ */

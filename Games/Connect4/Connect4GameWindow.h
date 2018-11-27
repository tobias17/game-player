#ifndef CONNECT_4_GAME_WINDOW_H_
#define CONNECT_4_GAME_WINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>
#include <QPalette>
#include <QThread>
#include "../../Engines/EngineHandler.h"
#include "../../Engines/RandomMoveEngine/RandomMoveEngine.h"
#include "Connect4Game.h"
#include "../GameWindow.h"

class Connect4GameWindow : public GameWindow {
	Q_OBJECT
public:
	Connect4GameWindow(Connect4Settings_t, Engine*, Engine*);
	~Connect4GameWindow() {};
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
	QPalette p1Palette;
	QPalette p2Palette;
	QPalette backPalette;
	QSignalMapper* signalMapper;
	Connect4Game* game;
	Connect4Settings_t settings;
};

#endif /* CONNECT_4_GAME_WINDOW_H_ */

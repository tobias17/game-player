#ifndef CONNECT_4_GAME_WINDOW_H_
#define CONNECT_4_GAME_WINDOW_H_

//*****************************************************************************
//Includes

#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QPushButton>
#include <QPalette>
#include <QThread>
#include "../../Engines/EngineHandler.h"
#include "../../Engines/RandomMoveEngine/RandomMoveEngine.h"
#include "../GameWindow.h"
#include "Connect4Game.h"

class Connect4GameWindow : public GameWindow {
	Q_OBJECT
public:
	Connect4GameWindow(Connect4Settings, Engine*, Engine*);
	~Connect4GameWindow() {};
	void setEngine(Engine*, int player);
	enum EngineHandlerIndecies { p1Engine, p2Engine };
private:
	void updateUI();
	QPalette p1Palette;
	QPalette p2Palette;
	QPalette backPalette;
	QSignalMapper* signalMapper;
	Connect4Settings settings;
};

#endif /* CONNECT_4_GAME_WINDOW_H_ */

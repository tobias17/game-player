//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QSignalMapper>
#include <QWidget>
#include <QPushButton>
#include <QThread>
#include "TicTacToeGame.h"
#include "../../Engines/EngineHandler.h"
#include "../../Engines/RandomMoveEngine/RandomMoveEngine.h"

#define PLAYER_1_CHAR	"X"
#define PLAYER_2_CHAR	"O"

class TicTacToeGameWindow : public QWidget {
	Q_OBJECT
public:
	TicTacToeGameWindow(TicTacToeSettings_t, Engine*, Engine*);
	~TicTacToeGameWindow();
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
	vector<QPushButton*> buttons;
	QMessageBox* messageBox;
	EngineHandler* engineHandlers[2];
	TicTacToeSettings_t settings;
	QThread workerThread;
};

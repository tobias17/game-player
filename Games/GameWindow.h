#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

//*****************************************************************************
//Includes
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "../Engines/EngineHandler.h"

class GameWindow : public QWidget {
	Q_OBJECT
public:
	GameWindow(Game*, Engine*, Engine*);
	~GameWindow() {};
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
protected:
	Game* game;
	vector<QPushButton*> buttons;
	QMessageBox* messageBox;
	EngineHandler* engineHandlers[2];
	QThread workerThread;
private:
	virtual void updateUI() = 0;
	void checkForWinner();
	void closeEvent(QCloseEvent *bar);
};

#endif /* GAME_WINDOW_H_ */

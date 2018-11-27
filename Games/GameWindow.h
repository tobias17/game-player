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
	GameWindow(Engine*, Engine*);
	~GameWindow() {};
	void setEngine(Engine*, int player);
	enum EngineHandlerIndecies { p1Engine, p2Engine };
protected:
	vector<QPushButton*> buttons;
	QMessageBox* messageBox;
	EngineHandler* engineHandlers[2];
	QThread workerThread;
private:
	void closeEvent(QCloseEvent *bar);
};

#endif /* GAME_WINDOW_H_ */

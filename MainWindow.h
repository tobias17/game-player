#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QListWidget>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include "WindowConstants.h"
#include "Games/TicTacToe/TicTacToeGameWindow.h"
#include "Games/Connect4/Connect4GameWindow.h"
#include "Engines/RandomMoveEngine/RandomMoveEngine.h"
#include "Engines/NaiveTreeSearch/NaiveTreeSearchEngine.h"

//*****************************************************************************
//Defines
#define GAME_COUNT 1

using namespace std;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
	enum PlayerIndexes { p1Index = 0, p2Index };
private slots:
	void gameSettingsButtonHandler();
	void p1SettingsButtonHandler();
	void p2SettingsButtonHandler();
	void startGameButtonHandler();
private:
	void generalSettingsHandler(int index);
	QListWidget* gameList;
	QListWidget* p1List;
	QListWidget* p2List;
	QPushButton* gameSettingsButton;
	QPushButton* p1SettingsButton;
	QPushButton* p2SettingsButton;
	QPushButton* startGameButton;
	vector<QString> games;
	vector<QString> engines;

	// games
	GeneralSettingsWindow* ticTacToeSettingsWindow;
	GeneralSettingsWindow* connect4SettingsWindow;

	// engines
	GeneralSettingsWindow* randomMoveSettingsWindows[2];
	GeneralSettingsWindow* naiveTreeSearchSettingsWindows[2];
};

//*****************************************************************************

#endif /* MAIN_WINDOW_H_ */

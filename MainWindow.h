#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QListWidget>
#include <QThread>
#include <QLabel>
#include <QPushButton>
#include "TicTacToe/TicTacToeGame.h"
#include "WindowConstants.h"

//*****************************************************************************
//Defines
#define GAME_COUNT 1

//namespace Ui
//{
//	class MainWindow;
//}
using namespace std;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
private slots:
	void gameSettingsButtonHandler();
	void receiveTicTacToeSettings(TicTacToeSettings_t);
	void p1SettingsButtonHandler();
	void p2SettingsButtonHandler();
	void startGameButtonHandler();
private:
	QListWidget* gameList;
	QListWidget* p1List;
	QListWidget* p2List;
	QPushButton* gameSettingsButton;
	QPushButton* p1SettingsButton;
	QPushButton* p2SettingsButton;
	QPushButton* startGameButton;
	vector<QString> games;
	vector<QString> players;
//	vector<QThread> threads;

	TicTacToeSettings_t tttSettings;
	TicTacToeSettingsWindow* tttSettingsWindow;
};

//*****************************************************************************

#endif /* MAINWINDOW_H_ */

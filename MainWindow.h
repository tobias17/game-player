#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include "TicTacToe/TicTacToeGame.h"

//*****************************************************************************
//Defines
#define GAP_SIZE 20
#define ITEM_WIDTH 150
#define LIST_HEIGHT 200
#define BUTTON_HEIGHT 50
#define GAME_COUNT 1

//namespace Ui
//{
//	class MainWindow;
//}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
private slots:
	void test();
private:

	TicTacToeGame* game;

	QListWidget* list;
	QPushButton* gameSettingsButton;
	std::vector<QString> games;
};

//*****************************************************************************

#endif /* MAINWINDOW_H_ */

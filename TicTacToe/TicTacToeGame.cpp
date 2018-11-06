//*****************************************************************************
//Includes
#include "TicTacToeGame.h"

//TicTacToeGame::TicTacToeGame() : QWidget(0) {
//	TicTacToeSettings_t setting;
//	TicTacToeGame(setting);
//}

TicTacToeGame::TicTacToeGame(TicTacToeSettings_t aSetting) : QWidget(0) {
	settings = aSetting;

	int squareCount = settings.squareCount;
	QSize size = QSize(settings.squareSize, settings.squareSize);
	for (int x = 0; x < squareCount; x++) {
		for (int y = 0; y < squareCount; y++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.gapSize + x*settings.squareSize, (y+1)*settings.gapSize + y*settings.squareSize);
			button->setGeometry(QRect(loc, size));
			buttons.push_back(button);
		}
	}

	QSize windowSize = QSize((squareCount+1)*settings.gapSize + squareCount*settings.squareSize, (squareCount+1)*settings.gapSize + squareCount*settings.squareSize);
	this->setFixedSize(windowSize);
}

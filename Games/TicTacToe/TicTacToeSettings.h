#ifndef TIC_TAC_TOE_SETTINGS_H_
#define TIC_TAC_TOE_SETTINGS_H_

//*****************************************************************************
//Includes
#include <iostream>
#include "../../WindowConstants.h"
#include "../../GeneralSettingsWindow.h"

//*****************************************************************************
//Defines

struct TicTacToeSettings_t {
	int squareCount = 3;
	int squaresToWin = 3;
	int squareSize = 100;
	int gapSize = 8;
};

class TicTacToeSettingsController : public QObject {
	Q_OBJECT
public:
	TicTacToeSettingsController();
	void showWindow();
	TicTacToeSettings_t getSettings() { return settings; };
public slots:
	void receiveSettings(vector<QString>);
signals:
	void sendCloseWindow();
private:
	TicTacToeSettings_t settings;
	GeneralSettingsWindow* settingsWindow;
	void showError(QString text);
};

#endif /* TIC_TAC_TOE_SETTINGS_H_ */

#ifndef CONNECT_4_SETTINGS_H_
#define CONNECT_4_SETTINGS_H_

//*****************************************************************************
//Includes
#include <iostream>
#include "../../WindowConstants.h"
#include "../../GeneralSettingsWindow.h"

//*****************************************************************************
//Defines

struct Connect4Settings_t {
	int height = 6;
	int width = 7;
	int squaresToWin = 4;
	int squareSize = 80;
	int gapSize = 6;
};

class Connect4SettingsController : public QObject {
	Q_OBJECT
public:
	Connect4SettingsController();
	void showWindow();
	Connect4Settings_t getSettings() { return settings; };
public slots:
	void receiveSettings(vector<QString>);
signals:
	void sendCloseWindow();
private:
	Connect4Settings_t settings;
	GeneralSettingsWindow* settingsWindow;
	void showError(QString text);
};

#endif /* CONNECT_4_SETTINGS_H_ */

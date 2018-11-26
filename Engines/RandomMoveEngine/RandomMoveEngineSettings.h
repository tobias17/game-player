#ifndef RANDOM_MOVE_ENGINE_SETTINGS_H_
#define RANDOM_MOVE_ENGINE_SETTINGS_H_

//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

struct RandomMoveEngineSettings_t {
	int moveDelay_ms = 0;
};

class RandomMoveEngineSettingsController : public QObject {
	Q_OBJECT
public:
	RandomMoveEngineSettingsController();
	void showWindow();
	RandomMoveEngineSettings_t getSettings() { return settings; };
signals:
	void sendCloseWindow();
public slots:
	void receiveSettings(vector<QString>);
private:
	RandomMoveEngineSettings_t settings;
	GeneralSettingsWindow* settingsWindow;
};

#endif /* RANDOM_MOVE_ENGINE_SETTINGS_H_ */

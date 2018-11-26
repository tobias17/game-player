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
public slots:
	void receiveSettings(vector<QString>);
private:
	RandomMoveEngineSettings_t settings;
	GeneralSettingsWindow* settingsWindow;
};

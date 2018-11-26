//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

struct NaiveTreeSearchEngineSettings_t {
	int timePerMove_ms = 1000;
};

class NaiveTreeSearchEngineSettingsController : public QObject {
	Q_OBJECT
public:
	NaiveTreeSearchEngineSettingsController();
	void showWindow();
	NaiveTreeSearchEngineSettings_t getSettings() { return settings; };
public slots:
	void receiveSettings(vector<QString>);
private:
	NaiveTreeSearchEngineSettings_t settings;
	GeneralSettingsWindow* settingsWindow;
};

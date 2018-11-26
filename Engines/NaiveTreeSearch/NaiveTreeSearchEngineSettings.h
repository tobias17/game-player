#ifndef NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_
#define NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_

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
signals:
	void sendCloseWindow();
public slots:
	void receiveSettings(vector<QString>);
private:
	NaiveTreeSearchEngineSettings_t settings;
	GeneralSettingsWindow* settingsWindow;
};

#endif /* NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_ */

//*****************************************************************************
//Includes
#include "NaiveTreeSearchEngineSettings.h"

NaiveTreeSearchEngineSettingsController::NaiveTreeSearchEngineSettingsController() : QObject(0) {
	vector<QString> names;
	vector<QString> values;

	names.push_back("Move Time (ms)");
	values.push_back(QString::number(settings.timePerMove_ms));

	settingsWindow = new GeneralSettingsWindow(names, values, "Naive Tree Search Engine Settings");
	connect(settingsWindow, SIGNAL (sendSettings(vector<QString>)), this, SLOT (receiveSettings(vector<QString>)));
}

void NaiveTreeSearchEngineSettingsController::showWindow() {
	vector<QString> values;
	values.push_back(QString::number(settings.timePerMove_ms));
	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void NaiveTreeSearchEngineSettingsController::receiveSettings(vector<QString> values) {
	if (values.size() != 1) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}
	settings.timePerMove_ms = values.at(0).toInt();
}

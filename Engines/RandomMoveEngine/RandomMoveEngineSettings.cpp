//*****************************************************************************
//Includes
#include "RandomMoveEngineSettings.h"

RandomMoveEngineSettingsController::RandomMoveEngineSettingsController() : QObject(0) {
	vector<QString> names;
	vector<QString> values;

	names.push_back("Move Delay (ms)");
	values.push_back(QString::number(settings.moveDelay_ms));

	settingsWindow = new GeneralSettingsWindow(names, values, "Random Move Engine Settings");
	connect(settingsWindow, SIGNAL (sendSettings(vector<QString>)), this, SLOT (receiveSettings(vector<QString>)));
}

void RandomMoveEngineSettingsController::showWindow() {
	vector<QString> values;
	values.push_back(QString::number(settings.moveDelay_ms));
	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void RandomMoveEngineSettingsController::receiveSettings(vector<QString> values) {
	if (values.size() != 1) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}
	settings.moveDelay_ms = values.at(0).toInt();
}

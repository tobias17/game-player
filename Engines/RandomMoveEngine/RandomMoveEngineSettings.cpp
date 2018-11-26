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
	connect(this, SIGNAL (sendCloseWindow()), settingsWindow, SLOT (receiveCloseWindow()));
}

void RandomMoveEngineSettingsController::showWindow() {
	vector<QString> values;
	values.push_back(QString::number(settings.moveDelay_ms));
	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void RandomMoveEngineSettingsController::receiveSettings(vector<QString> values) {
	RandomMoveEngineSettings_t newSettings;
	bool ok;

	if (values.size() != 1) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}

	newSettings.moveDelay_ms = values.at(0).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Move Delay to Integer");
		return;
	}

	if (newSettings.moveDelay_ms < 0) {
		settingsWindow->showError("Move Delay out of range");
		return;
	}

	settings = newSettings;
	emit sendCloseWindow();
}


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
	connect(this, SIGNAL (sendCloseWindow()), settingsWindow, SLOT (receiveCloseWindow()));
}

void NaiveTreeSearchEngineSettingsController::showWindow() {
	vector<QString> values;
	values.push_back(QString::number(settings.timePerMove_ms));
	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void NaiveTreeSearchEngineSettingsController::receiveSettings(vector<QString> values) {
	NaiveTreeSearchEngineSettings_t newSettings;
	bool ok;

	if (values.size() != 1) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}

	newSettings.timePerMove_ms = values.at(0).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Move Delay to Integer");
		return;
	}

	if (newSettings.timePerMove_ms < 0) {
		settingsWindow->showError("Move Delay out of range");
		return;
	}

	settings = newSettings;
	emit sendCloseWindow();
}

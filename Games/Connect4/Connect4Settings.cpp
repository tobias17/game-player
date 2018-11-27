//*****************************************************************************
//Includes
#include "Connect4Settings.h"

Connect4SettingsController::Connect4SettingsController() : QObject(0) {
	vector<QString> names;
	vector<QString> values;

	names.push_back("Height");
	values.push_back(QString::number(settings.height));

	names.push_back("Width");
	values.push_back(QString::number(settings.width));

	names.push_back("Squares to Win");
	values.push_back(QString::number(settings.squaresToWin));

	names.push_back("Square Size");
	values.push_back(QString::number(settings.squareSize));

	names.push_back("Gap Size");
	values.push_back(QString::number(settings.gapSize));

	settingsWindow = new GeneralSettingsWindow(names, values, "Connect 4 Settings");
	connect(settingsWindow, SIGNAL (sendSettings(vector<QString>)), this, SLOT (receiveSettings(vector<QString>)));
	connect(this, SIGNAL (sendCloseWindow()), settingsWindow, SLOT (receiveCloseWindow()));
}

void Connect4SettingsController::showWindow() {
	vector<QString> values;

	values.push_back(QString::number(settings.height));
	values.push_back(QString::number(settings.width));
	values.push_back(QString::number(settings.squaresToWin));
	values.push_back(QString::number(settings.squareSize));
	values.push_back(QString::number(settings.gapSize));

	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void Connect4SettingsController::receiveSettings(vector<QString> values) {
	Connect4Settings_t newSettings;
	bool ok;

	if (values.size() != 5) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}

	newSettings.height = values.at(0).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Height to Integer");
		return;
	}
	newSettings.width = values.at(1).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Width to Integer");
		return;
	}
	newSettings.squaresToWin = values.at(2).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Squares to Win to Integer");
		return;
	}
	newSettings.squareSize = values.at(3).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Square Size to Integer");
		return;
	}
	newSettings.gapSize = values.at(4).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Gap Size to Integer");
		return;
	}

	if (newSettings.height < 1) {
		settingsWindow->showError("Height out of range");
		return;
	}
	if (newSettings.width < 1) {
		settingsWindow->showError("Width out of range");
		return;
	}
	if (newSettings.squaresToWin < 1 || (newSettings.squaresToWin > newSettings.width && newSettings.squaresToWin > newSettings.height)) {
		settingsWindow->showError("Squares to Win out of range");
		return;
	}
	if (newSettings.squareSize < 1) {
		settingsWindow->showError("Square Size out of range");
		return;
	}
	if (newSettings.gapSize < 1) {
		settingsWindow->showError("Gap Size out of range");
		return;
	}

	settings = newSettings;
	emit sendCloseWindow();
}



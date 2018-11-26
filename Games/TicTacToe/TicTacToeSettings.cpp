//*****************************************************************************
//Includes
#include "TicTacToeSettings.h"

TicTacToeSettingsController::TicTacToeSettingsController() : QObject(0) {
	vector<QString> names;
	vector<QString> values;

	names.push_back("Square Count");
	values.push_back(QString::number(settings.squareCount));

	names.push_back("Squares to Win");
	values.push_back(QString::number(settings.squaresToWin));

	names.push_back("Square Size");
	values.push_back(QString::number(settings.squareSize));

	names.push_back("Gap Size");
	values.push_back(QString::number(settings.gapSize));

	settingsWindow = new GeneralSettingsWindow(names, values, "Random Move Engine Settings");
	connect(settingsWindow, SIGNAL (sendSettings(vector<QString>)), this, SLOT (receiveSettings(vector<QString>)));
	connect(this, SIGNAL (sendCloseWindow()), settingsWindow, SLOT (receiveCloseWindow()));
}

void TicTacToeSettingsController::showWindow() {
	vector<QString> values;

	values.push_back(QString::number(settings.squareCount));
	values.push_back(QString::number(settings.squaresToWin));
	values.push_back(QString::number(settings.squareSize));
	values.push_back(QString::number(settings.gapSize));

	settingsWindow->updateValues(values);
	settingsWindow->show();
}

void TicTacToeSettingsController::receiveSettings(vector<QString> values) {
	TicTacToeSettings_t newSettings;
	bool ok;

	if (values.size() != 4) {
		settingsWindow->showError("Incorrect number of values passed back from Random Move Engine Settings");
		return;
	}

	newSettings.squareCount = values.at(0).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Square Count to Integer");
		return;
	}
	newSettings.squaresToWin = values.at(1).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Squares to Win to Integer");
		return;
	}
	newSettings.squareSize = values.at(2).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Square Size to Integer");
		return;
	}
	newSettings.gapSize = values.at(3).toInt(&ok);
	if (!ok) {
		settingsWindow->showError("Error converting Gap Size to Integer");
		return;
	}

	if (newSettings.squareCount < 1) {
		settingsWindow->showError("Square Count out of range");
		return;
	}
	if (newSettings.squaresToWin < 1 || newSettings.squaresToWin > newSettings.squareCount) {
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



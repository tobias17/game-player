#ifndef GENERAL_SETTINGS_WINDOW_H_
#define GENERAL_SETTINGS_WINDOW_H_

//*****************************************************************************
//Includes
#include <iostream>
#include <vector>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "WindowConstants.h"
#include "GeneralSettings.h"

using namespace std;

class GeneralSettingsWindow : public QWidget {
	Q_OBJECT
public:
	GeneralSettingsWindow(GeneralSettings*);
	void showError(QString);
	void updateValues(GeneralSettings*);
	GeneralSettings* getSettings() { return settings; };
public slots:
	void receiveCloseWindow();
signals:
	void sendSettings(vector<QString>);
private slots:
	void saveButtonHandler();
private:
	GeneralSettings* settings;
	vector<QLineEdit*> lineEdits;
	QPushButton* saveButton;
	QPushButton* closeButton;
};

//*****************************************************************************

#endif /* GENERAL_SETTINGS_WINDOW_H_ */

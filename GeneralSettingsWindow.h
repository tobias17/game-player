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

using namespace std;

class GeneralSettingsWindow : public QWidget {
	Q_OBJECT
public:
	GeneralSettingsWindow(vector<QString> names, vector<QString> values, QString windowTitle);
	void showError(QString);
	void updateValues(vector<QString>);
signals:
	void sendSettings(vector<QString>);
private slots:
	void saveButtonHandler();
	void closeButtonHandler();
private:
	vector<QLineEdit*> lineEdits;
	QPushButton* saveButton;
	QPushButton* closeButton;
};

//*****************************************************************************

#endif /* GENERAL_SETTINGS_WINDOW_H_ */

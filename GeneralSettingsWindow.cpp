//*****************************************************************************
//Includes
#include "GeneralSettingsWindow.h"

GeneralSettingsWindow::GeneralSettingsWindow(GeneralSettings* aSetting) : QWidget(0) {
	// set the internal settings to those passed in
	settings = aSetting;

	// create a QSize for the button size
	QSize size = QSize(S_ITEM_WIDTH, S_ITEM_HEIGHT);
	// initialize x and y location counters
	int y = S_GAP_SIZE;
	int x = S_GAP_SIZE;
	// loop through all of the settings
	for (int i = 0; i < settings->size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		// create a new label and set the text to the setting name
		QLabel* label = new QLabel(settings->getName(i), this);
		// set the label's location and size
		label->setGeometry(QRect(QPoint(x, y), size));
	}
	// create a save button
	saveButton = new QPushButton("Save", this);
	// set the button's location and size
	saveButton->setGeometry(QRect(QPoint(x, y), size));

	// reset the x and y location counters
	y = S_GAP_SIZE;
	x = 2*S_GAP_SIZE + S_ITEM_WIDTH;
	// loop through all of the settings
	for (int i = 0; i < settings->size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		// create a line edit and set it to the default value of the setting
		QLineEdit* lineEdit = new QLineEdit(QString::number(settings->get(i)), this);
		// set the line edit's location and size
		lineEdit->setGeometry(QRect(QPoint(x, y), size));
		// add the line edit to a vector for later access
		lineEdits.push_back(lineEdit);
	}
	// create a close button
	closeButton = new QPushButton("Close", this);
	// set the close button's location and size
	closeButton->setGeometry(QRect(QPoint(x, y), size));

	// connect the save and close buttons to their handlers
	connect(saveButton, SIGNAL (released()), this, SLOT (saveButtonHandler()));
	connect(closeButton, SIGNAL (released()), this, SLOT (receiveCloseWindow()));

	// set the window size and title
	int height = max(saveButton->y(), closeButton->y()) + S_GAP_SIZE + S_ITEM_HEIGHT;
	this->setFixedSize(3*S_GAP_SIZE + 2*S_ITEM_WIDTH, height);
	this->setWindowTitle(settings->getSettingsName());
}

void GeneralSettingsWindow::updateAndShow() {
	// loop through all settings
	for (int i = 0; i < settings->size(); i++) {
		// set the line edit's text to the setting's value
		lineEdits.at(i)->setText(QString::number(settings->get(i)));
	}
	// show the window
	this->show();
}

void GeneralSettingsWindow::showError(QString text) {
	// create a new message box
	QMessageBox* messageBox = new QMessageBox();
	// set the message box's title and text
	messageBox->setWindowTitle("Error");
	messageBox->setText(text);
	// show the message box
	messageBox->exec();
}

void GeneralSettingsWindow::saveButtonHandler() {
	// create a new setting of the same type as that stored
	GeneralSettings* newSettings = settings->blank();
	// loop through all settings
	for (int i = 0; i < settings->size(); i++) {
		// create a boolean to save whether the integer conversion worked
		bool ok;
		// attempt to set the setting to the value in the line edit
		bool good = newSettings->set(i, lineEdits[i]->text().toInt(&ok));
		// check to see if integer conversion worked
		if (!ok) {
			// if not tell the user and return
			showError("Error converting " + newSettings->getName(i) + " to integer");
			return;
		}
		// check to see if the new setting value was accepted
		if (!good) {
			// if not tell the user and return
			showError(newSettings->getName(i) + " value not in range");
			return;
		}
	}
	// check to see if the new setting is consistent
	if (!newSettings->getIsConsistent()) {
		// if not tell the user and return
		showError("Values are not consistent");
		return;
	}

	// set the internal settings to the new ones just created
	settings = newSettings;
	// close this window since values were accepted
	this->close();
}

void GeneralSettingsWindow::receiveCloseWindow() {
	// close the window
	this->close();
}



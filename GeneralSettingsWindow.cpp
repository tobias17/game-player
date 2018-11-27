//*****************************************************************************
//Includes
#include "GeneralSettingsWindow.h"

GeneralSettingsWindow::GeneralSettingsWindow(GeneralSettings* aSetting) : QWidget(0) {
	settings = aSetting;
	QSize size = QSize(S_ITEM_WIDTH, S_ITEM_HEIGHT);

	int y = S_GAP_SIZE;
	int x = S_GAP_SIZE;
	for (int i = 0; i < settings->size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		QLabel* label = new QLabel(settings->getName(i), this);
		label->setGeometry(QRect(QPoint(x, y), size));
	}
	saveButton = new QPushButton("Save", this);
	saveButton->setGeometry(QRect(QPoint(x, y), size));

	y = S_GAP_SIZE;
	x = 2*S_GAP_SIZE + S_ITEM_WIDTH;
	for (int i = 0; i < settings->size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		QLineEdit* lineEdit = new QLineEdit(QString::number(settings->get(i)), this);
		lineEdit->setGeometry(QRect(QPoint(x, y), size));
		lineEdits.push_back(lineEdit);
	}
	closeButton = new QPushButton("Close", this);
	closeButton->setGeometry(QRect(QPoint(x, y), size));

	connect(saveButton, SIGNAL (released()), this, SLOT (saveButtonHandler()));
	connect(closeButton, SIGNAL (released()), this, SLOT (receiveCloseWindow()));

	int height = max(saveButton->y(), closeButton->y()) + S_GAP_SIZE + S_ITEM_HEIGHT;
	this->setFixedSize(3*S_GAP_SIZE + 2*S_ITEM_WIDTH, height);
	this->setWindowTitle(settings->getSettingsName());
}

void GeneralSettingsWindow::updateValues(GeneralSettings* aSetting) {
	if (settings->getSettingsName() != aSetting->getSettingsName()) {
		showError("Wrong type of setting sent to window");
		return;
	}
	for (int i = 0; i < aSetting->size(); i++) {
		lineEdits.at(i)->setText(QString::number(aSetting->get(i)));
	}
}

void GeneralSettingsWindow::showError(QString text) {
	QMessageBox* messageBox = new QMessageBox();
	messageBox->setWindowTitle("Error");
	messageBox->setText(text);
	messageBox->exec();
}

void GeneralSettingsWindow::saveButtonHandler() {
	GeneralSettings* newSettings = settings->blank();
	for (int i = 0; i < settings->size(); i++) {
		bool ok;
		bool good = newSettings->set(i, lineEdits[i]->text().toInt(&ok));
		if (!ok) {
			showError("Error converting " + newSettings->getName(i) + " to integer");
			return;
		}
		if (!good) {
			showError(newSettings->getName(i) + " value not in range");
			return;
		}
	}
	if (!newSettings->getIsConsistent()) {
		showError("Values are not consistent");
		return;
	}
	settings = newSettings;
	this->close();
}

void GeneralSettingsWindow::receiveCloseWindow() {
	this->close();
}



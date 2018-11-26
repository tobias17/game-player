//*****************************************************************************
//Includes
#include "GeneralSettingsWindow.h"

GeneralSettingsWindow::GeneralSettingsWindow(vector<QString> names, vector<QString> values, QString windowTitle) : QWidget(0) {
	QSize size = QSize(S_ITEM_WIDTH, S_ITEM_HEIGHT);

	int y = S_GAP_SIZE;
	int x = S_GAP_SIZE;
	for (uint i = 0; i < names.size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		QLabel* label = new QLabel(names.at(i), this);
		label->setGeometry(QRect(QPoint(x, y), size));
	}
	saveButton = new QPushButton("Save", this);
	saveButton->setGeometry(QRect(QPoint(x, y), size));

	y = S_GAP_SIZE;
	x = 2*S_GAP_SIZE + S_ITEM_WIDTH;
	for (uint i = 0; i < values.size(); i++, y += S_GAP_SIZE + S_ITEM_HEIGHT) {
		QLineEdit* lineEdit = new QLineEdit(values.at(i), this);
		lineEdit->setGeometry(QRect(QPoint(x, y), size));
		lineEdits.push_back(lineEdit);
	}
	closeButton = new QPushButton("Close", this);
	closeButton->setGeometry(QRect(QPoint(x, y), size));

	connect(saveButton, SIGNAL (released()), this, SLOT (saveButtonHandler()));
	connect(closeButton, SIGNAL (released()), this, SLOT (closeButtonHandler()));

	int height = max(saveButton->y(), closeButton->y()) + S_GAP_SIZE + S_ITEM_HEIGHT;
	this->setFixedSize(3*S_GAP_SIZE + 2*S_ITEM_WIDTH, height);
	this->setWindowTitle(windowTitle);
}

void GeneralSettingsWindow::updateValues(vector<QString> values) {
	if (values.size() != lineEdits.size()) {
		showError("Incorrect number of values sent to General Settings Window");
		return;
	}
	for (uint i = 0; i < values.size(); i++) {
		lineEdits.at(i)->setText(values.at(i));
	}
}

void GeneralSettingsWindow::showError(QString text) {
	QMessageBox* messageBox = new QMessageBox();
	messageBox->setWindowTitle("Error");
	messageBox->setText(text);
	messageBox->exec();
}

void GeneralSettingsWindow::saveButtonHandler() {
	vector<QString> values;
	for (uint i = 0; i < lineEdits.size(); i++) {
		values.push_back(lineEdits.at(i)->text());
	}
	emit sendSettings(values);
}

void GeneralSettingsWindow::closeButtonHandler() {
	this->close();
}

void GeneralSettingsWindow::receiveCloseWindow() {
	this->close();
}



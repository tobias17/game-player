//*****************************************************************************
//Includes
#include "NPlayerTTTSettings.h"

NPlayerTTTSettingsWindow::NPlayerTTTSettingsWindow() : QWidget(0) {
	squareCountEdit = new QLineEdit(this);
	squaresToWinEdit = new QLineEdit(this);
	squareSizeEdit = new QLineEdit(this);
	gapSizeEdit = new QLineEdit(this);

	squareCountEdit->setText(QString::number(settings.squareCount));
	squaresToWinEdit->setText(QString::number(settings.squaresToWin));
	squareSizeEdit->setText(QString::number(settings.squareSize));
	gapSizeEdit->setText(QString::number(settings.gapSize));

	int y = S_GAP_SIZE;
	int x = S_GAP_SIZE;
	QSize itemSize = QSize(S_ITEM_WIDTH, S_ITEM_HEIGHT);
	squareCountEdit->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	squaresToWinEdit->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	squareSizeEdit->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	gapSizeEdit->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;

	saveButton = new QPushButton("Save", this);
	saveButton->setGeometry(QRect(QPoint(x, y), itemSize));
	connect(saveButton, SIGNAL (released()), this, SLOT (saveButtonHandler()));

	QLabel* squareCountLabel = new QLabel("Square Count", this);
	QLabel* squaresToWinLabel = new QLabel("Squares to Win", this);
	QLabel* squareSizeLabel = new QLabel("Square Size", this);
	QLabel* gapSizeLabel = new QLabel("Gap Size", this);

	y = S_GAP_SIZE;
	x = S_GAP_SIZE*2 + S_ITEM_WIDTH;
	squareCountLabel->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	squaresToWinLabel->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	squareSizeLabel->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;
	gapSizeLabel->setGeometry(QRect(QPoint(x, y), itemSize));
	y += S_GAP_SIZE + S_ITEM_HEIGHT;

	closeButton = new QPushButton("Close", this);
	closeButton->setGeometry(QRect(QPoint(x, y), itemSize));
	connect(closeButton, SIGNAL (released()), this, SLOT (closeButtonHandler()));

	messageBox = new QMessageBox();
	messageBox->setWindowTitle("Error");

	this->setFixedSize(x + S_ITEM_WIDTH + S_GAP_SIZE, y + S_ITEM_HEIGHT + S_GAP_SIZE);
	this->setWindowTitle("Tic Tac Toe Settings");
}

void NPlayerTTTSettingsWindow::setSettings(NPlayerTTTSettings_t aSetting) {
	settings = aSetting;
	squareCountEdit->setText(QString::number(settings.squareCount));
	squaresToWinEdit->setText(QString::number(settings.squaresToWin));
	squareSizeEdit->setText(QString::number(settings.squareSize));
	gapSizeEdit->setText(QString::number(settings.gapSize));
}

void NPlayerTTTSettingsWindow::saveButtonHandler() {
	NPlayerTTTSettings_t newSettings;
	bool ok;

	newSettings.squareCount = squareCountEdit->text().toInt(&ok);
	if (!ok) {
		showError("Error converting Square Count to Integer");
		return;
	}

	newSettings.squaresToWin = squaresToWinEdit->text().toInt(&ok);
	if (!ok) {
		showError("Error converting Squares to Win to Integer");
		return;
	}

	newSettings.squareSize = squareSizeEdit->text().toInt(&ok);
	if (!ok) {
		showError("Error converting Square Size to Integer");
		return;
	}

	newSettings.gapSize = gapSizeEdit->text().toInt(&ok);
	if (!ok) {
		showError("Error converting Gap Size to Integer");
		return;
	}

	if (newSettings.squareCount < 1) {
		showError("Square Count out of range");
		return;
	}
	if (newSettings.squaresToWin < 1 || newSettings.squaresToWin > newSettings.squareCount) {
		showError("Squares to Win out of range");
		return;
	}
	if (newSettings.squareSize < 1) {
		showError("Square Size out of range");
		return;
	}
	if (newSettings.gapSize < 1) {
		showError("Gap Size out of range");
		return;
	}

	emit sendTicTacToeSettings(newSettings);
}

void NPlayerTTTSettingsWindow::closeButtonHandler() {
	this->hide();
}

void NPlayerTTTSettingsWindow::showError(QString text) {
	messageBox->setText(text);
	messageBox->exec();
}

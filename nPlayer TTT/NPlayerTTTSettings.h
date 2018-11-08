//*****************************************************************************
//Includes
#include <iostream>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include "../WindowConstants.h"

//*****************************************************************************
//Defines

struct NPlayerTTTSettings_t {
	int squareCount = 3;
	int squaresToWin = 3;
	int squareSize = 100;
	int gapSize = 8;
};

class NPlayerTTTSettingsWindow : public QWidget {
	Q_OBJECT
public:
	NPlayerTTTSettingsWindow();
//	TicTacToeSettingsWindow(TicTacToeSettings_t);
	void setSettings(NPlayerTTTSettings_t);
signals:
	void sendTicTacToeSettings(NPlayerTTTSettings_t);
private slots:
	void saveButtonHandler();
	void closeButtonHandler();
private:
	void showError(QString);
	NPlayerTTTSettings_t settings;
	QLineEdit* squareCountEdit;
	QLineEdit* squaresToWinEdit;
	QLineEdit* squareSizeEdit;
	QLineEdit* gapSizeEdit;
	QPushButton* saveButton;
	QPushButton* closeButton;
	QMessageBox* messageBox;
};

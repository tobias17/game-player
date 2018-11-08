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

struct TicTacToeSettings_t {
	int squareCount = 3;
	int squaresToWin = 3;
	int squareSize = 100;
	int gapSize = 8;
};

class TicTacToeSettingsWindow : public QWidget {
	Q_OBJECT
public:
	TicTacToeSettingsWindow();
//	TicTacToeSettingsWindow(TicTacToeSettings_t);
	void setSettings(TicTacToeSettings_t);
signals:
	void sendTicTacToeSettings(TicTacToeSettings_t);
private slots:
	void saveButtonHandler();
	void closeButtonHandler();
private:
	void showError(QString);
	TicTacToeSettings_t settings;
	QLineEdit* squareCountEdit;
	QLineEdit* squaresToWinEdit;
	QLineEdit* squareSizeEdit;
	QLineEdit* gapSizeEdit;
	QPushButton* saveButton;
	QPushButton* closeButton;
	QMessageBox* messageBox;
};

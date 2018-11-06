//*****************************************************************************
//Includes
#include "TicTacToeSettings.h"

TicTacToeSettingsWindow::TicTacToeSettingsWindow() : QWidget(0) {

}

TicTacToeSettingsWindow::TicTacToeSettingsWindow(TicTacToeSettings_t aSetting) : QWidget(0) {
	settings = aSetting;
	TicTacToeSettingsWindow();
}

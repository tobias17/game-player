//*****************************************************************************
//Includes
#include <vector>
#include <QWidget>
#include <QPushButton>
#include "TicTacToeSettings.h"

using namespace std;

class TicTacToeGame : public QWidget {
	Q_OBJECT
public:
	TicTacToeGame();
	TicTacToeGame(TicTacToeSettings_t);
private:
	TicTacToeSettings_t settings;
	vector<QPushButton*> buttons;
};

//*****************************************************************************
//Includes
#include <QWidget>

struct TicTacToeSettings_t {
	int squareCount = 3;
	int squaresToWin = 3;
	int squareSize = 200;
	int gapSize = 20;
};

class TicTacToeSettingsWindow : public QWidget {
	Q_OBJECT
public:
	TicTacToeSettingsWindow();
	TicTacToeSettingsWindow(TicTacToeSettings_t);
private:
	TicTacToeSettings_t settings;
};

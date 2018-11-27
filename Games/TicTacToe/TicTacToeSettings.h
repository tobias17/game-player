#ifndef TIC_TAC_TOE_SETTINGS_H_
#define TIC_TAC_TOE_SETTINGS_H_

//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

namespace TicTacToeNamespace {
	enum TicTacToeSettingsNames { squareCount, squaresToWin, squareSize, gapSize };
}
using namespace TicTacToeNamespace;

class TicTacToeSettings : public GeneralSettings {
public:
	TicTacToeSettings() : GeneralSettings("Tic Tac Toe Settings", 4) {
		vars[squareCount]  = new SettingsVariableLowerBound("Square Count", 3, 1);
		vars[squaresToWin] = new SettingsVariableLowerBound("Squares to Win", 3, 1);
		vars[squareSize]   = new SettingsVariableLowerBound("Square Size", 100, 1);
		vars[gapSize]      = new SettingsVariableLowerBound("Gap Size", 8, 1);
	};
	virtual ~TicTacToeSettings() {};
	GeneralSettings* blank() { return new TicTacToeSettings; };
	bool getIsConsistent() { return (vars[squaresToWin]->getValue() <= vars[squareCount]->getValue()); };
};

#endif /* TIC_TAC_TOE_SETTINGS_H_ */

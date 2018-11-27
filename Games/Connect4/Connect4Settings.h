#ifndef CONNECT_4_SETTINGS_H_
#define CONNECT_4_SETTINGS_H_

//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

namespace Connect4Namespace {
	enum Connect4SettingsNames { itemHeight, itemWidth, squaresToWin, squareSize, gapSize };
}
using namespace Connect4Namespace;

class Connect4Settings : public GeneralSettings {
public:
	Connect4Settings() : GeneralSettings("Connect 4 Settings", 5) {
		vars[itemHeight]                      = new SettingsVariableLowerBound("Height", 6, 1);
		vars[itemWidth]                       = new SettingsVariableLowerBound("Width", 7, 1);
		vars[Connect4Namespace::squaresToWin] = new SettingsVariableLowerBound("Squares to Win", 4, 1);
		vars[Connect4Namespace::squareSize]   = new SettingsVariableLowerBound("Square Size", 80, 1);
		vars[Connect4Namespace::gapSize]      = new SettingsVariableLowerBound("Gap Size", 6, 1);
	};
	virtual ~Connect4Settings() {};
	GeneralSettings* blank() { return new Connect4Settings; };
	bool getIsConsistent() { return (vars[Connect4Namespace::squaresToWin]->getValue() <= vars[itemHeight]->getValue()
			|| vars[Connect4Namespace::squaresToWin]->getValue() <= vars[itemWidth]->getValue()); };
};

#endif /* CONNECT_4_SETTINGS_H_ */

#ifndef RANDOM_MOVE_ENGINE_SETTINGS_H_
#define RANDOM_MOVE_ENGINE_SETTINGS_H_

//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

namespace RandomMoveNamespace {
	enum RandomMoveEngineSettingsNames { moveDelay_ms };
}
using namespace RandomMoveNamespace;

class RandomMoveSettings : public GeneralSettings {
public:
	RandomMoveSettings() : GeneralSettings("Random Move Engine Settings", 1) {
		vars[moveDelay_ms] = new SettingsVariableLowerBound("Move Delay (ms)", 0, 0);
	};
	virtual ~RandomMoveSettings() {};
	GeneralSettings* blank() { return new RandomMoveSettings; };
};

#endif /* RANDOM_MOVE_ENGINE_SETTINGS_H_ */

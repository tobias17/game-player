#ifndef NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_
#define NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_

//*****************************************************************************
//Includes
#include "../../GeneralSettingsWindow.h"

namespace NaiveTreeSearchNamespace {
	enum NaiveTreeSearchEngineSettingsNames { timePerMove_ms };
}
using namespace NaiveTreeSearchNamespace;

class NaiveTreeSearchSettings : public GeneralSettings {
public:
	NaiveTreeSearchSettings() : GeneralSettings("Naive Tree Search Engine Settings", 1) {
		vars[timePerMove_ms] = new SettingsVariableLowerBound("Move Time (ms)", 1000, 0);
	};
	virtual ~NaiveTreeSearchSettings() {};
	GeneralSettings* blank() { return new NaiveTreeSearchSettings; };
};

#endif /* NAIVE_TREE_SEARCH_ENGINE_SETTINGS_H_ */

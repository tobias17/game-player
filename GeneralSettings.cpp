//*****************************************************************************
//Includes
#include "GeneralSettings.h"

SettingsVariable::SettingsVariable() {
	name = "error";
	value = -1;
}

SettingsVariable::SettingsVariable(QString aName, int initValue) {
	 name = aName;
	 value = initValue;
}

bool SettingsVariable::set(int aValue) {
	value = aValue;
	return true;
}

SettingsVariableLowerBound::SettingsVariableLowerBound(QString aName, int initValue, int aLowerBound)
		: SettingsVariable(aName, initValue) {
	lowerBound = aLowerBound;
};

bool SettingsVariableLowerBound::set(int aValue) {
	if (aValue < lowerBound) return false;
	value = aValue;
	return true;
};

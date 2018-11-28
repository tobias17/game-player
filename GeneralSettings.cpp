//*****************************************************************************
//Includes
#include "GeneralSettings.h"

SettingsVariable::SettingsVariable() {
	// set default values - shows an error elsewhere in the code
	name = "error";
	value = -1;
}

SettingsVariable::SettingsVariable(QString aName, int initValue) {
	// set the internal variables to those passed in
	 name = aName;
	 value = initValue;
}

bool SettingsVariable::set(int aValue) {
	// set the internal value to that passed in
	value = aValue;
	// return true since there is nothing fail
	return true;
}

SettingsVariableLowerBound::SettingsVariableLowerBound(QString aName, int initValue, int aLowerBound)
		: SettingsVariable(aName, initValue) {
	// set the internal lower bound to that passed in
	lowerBound = aLowerBound;
};

bool SettingsVariableLowerBound::set(int aValue) {
	// check to see if the new value is above the lower bound
	if (aValue < lowerBound) return false;
	// set the internal value to that passed in
	value = aValue;
	// return true since the check earlier passed and the value is good
	return true;
};

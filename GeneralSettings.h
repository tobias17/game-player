#ifndef GENERAL_SETTINGS_H_
#define GENERAL_SETTINGS_H_

//*****************************************************************************
//Includes
#include <QString>

class SettingsVariable {
public:
	SettingsVariable();
	SettingsVariable(QString aName, int initValue);
	virtual ~SettingsVariable() {};
	virtual bool set(int aValue);
	QString getName() { return name; };
	int getValue() { return value; };
protected:
	QString name;
	int value;
};

class SettingsVariableLowerBound : public SettingsVariable {
public:
	SettingsVariableLowerBound(QString aName, int initValue, int aLowerBound);
	virtual ~SettingsVariableLowerBound() {};
	bool set(int aValue);
private:
	int lowerBound;
};

class GeneralSettings {
public:
	GeneralSettings(QString aSettingName, int aVariableCount) {
		settingsName = aSettingName;
		variableCount = aVariableCount;
		vars = new SettingsVariable*[variableCount];
	};
	virtual ~GeneralSettings() {};
	QString getSettingsName() { return settingsName; };
	int size() { return variableCount; };
	QString getName(int index) { return vars[index]->getName(); };
	int get(int index) { return vars[index]->getValue(); };
	int set(int index, int value) { return vars[index]->set(value); };
	virtual bool getIsConsistent() { return true; };
	virtual GeneralSettings* blank() = 0;
protected:
	QString settingsName;
	int variableCount;
	SettingsVariable** vars;
};

#endif /* GENERAL_SETTINGS_H_ */

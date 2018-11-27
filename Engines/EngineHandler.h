#ifndef ENGINE_HANDLER_H_
#define ENGINE_HANDLER_H_

//*****************************************************************************
//Includes
#include <QObject>
#include "Engine.h"

class EngineHandler : public QObject {
	Q_OBJECT
public:
	EngineHandler(Engine* aEngine) : QObject() { engine = aEngine; };
	bool getIsEngineHuman() { return engine->getIsHuman(); };
	void killEngine() { engine->killEngine(); };
public slots:
	void getMove(Game* game) { emit sendMove(engine->getMove(game)); };
signals:
	void sendMove(int id);
private:
	Engine* engine;
};

#endif /* ENGINE_HANDLER_H_ */

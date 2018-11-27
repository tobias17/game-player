#ifndef ENGINE_H_
#define ENGINE_H_

//*****************************************************************************
//Includes
#include <stdlib.h>
#include <iostream>
#include <QThread>
#include <mutex>
#include "../Games/Game.h"

class Engine {
public:
	virtual ~Engine() {};
	virtual int getMove(Game*) = 0;
	virtual bool getIsHuman() { return false; };
	void killEngine() { mut.lock(); running = false; mut.unlock(); };
protected:
	bool isRunning() { mut.lock(); bool b = running; mut.unlock(); return b; };
private:
	bool running = true;
	mutex mut;
};

class HumanEngine : public Engine {
public:
	int getMove(Game*) { std::cout << "human engine asked" << std::endl; return 0; };
	bool getIsHuman() { return true; };
};

#endif /* ENGINE_H_ */

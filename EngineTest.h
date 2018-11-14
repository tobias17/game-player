#include <iostream>

using namespace std;

class Engine {
public:
	virtual ~Engine() {};
	virtual void sayHello() = 0;
};

class Engine1 : public Engine {
public:
	void sayHello() { cout << "Hi" << endl; };
};

class Engine2 : public Engine {
public:
	void sayHello() { cout << "Hello" << endl; };
};

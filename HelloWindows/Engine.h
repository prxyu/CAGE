#ifndef _CAGE_ENGINE_H_
#define _CAGE_ENGINE_H_

#include "Game.h"
#include "Window.h"

class Engine {
private:
	int Loop();

public:
	static Game* game;
	static Window* window;

	Engine();
	~Engine();

	int Start(Game* level);
};

#endif
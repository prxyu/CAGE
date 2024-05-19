#ifndef _CAGE_ENGINE_H_
#define _CAGE_ENGINE_H_

#include "Game.h"
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"

class Engine {
private:
	static Timer timer;
	static bool paused;

	float DeltaTime();
	int Loop();

public:
	static Game* game;
	static Window* window;
	static Graphics* graphics;
	static float delta;

	Engine();
	~Engine();

	int Start(Game* level);

	static void Pause();
	static void Resume();
};

#endif
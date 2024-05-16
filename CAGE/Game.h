#ifndef _CAGE_GAME_H_
#define _CAGE_GAME_H_

#include "Window.h"

class Game {
protected:
	static Window*& window;

public:
	Game();
	virtual ~Game();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
};

#endif
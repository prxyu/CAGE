#include "Engine.h"
#include "Graphics.h"
#include <Windows.h>
#include <sstream>

Game* Engine::game = nullptr;
Window* Engine::window = nullptr;
Graphics* Engine::graphics = nullptr;
float Engine::delta = 0.0f;
bool Engine::paused = false;
Timer Engine::timer;

Engine::Engine() {
	window = new Window();
	graphics = new Graphics;
}

Engine::~Engine() {
	delete game;
	delete graphics;
	delete window;
}

int Engine::Start(Game* level) {
	game = level;

	if (!window->Create()) {
		MessageBox(nullptr, "Failed to create the window", "CAGE ERROR", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	if (!graphics->Initialize(window)) {
		MessageBox(window->Id(), "Failed to initialize graphics", "CAGE ERROR", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	timeBeginPeriod(1);
	
	int CExit_code = Loop();

	timeEndPeriod(1);

	return CExit_code;
}

void Engine::Pause() {
	paused = true;
	timer.Stop();
}

void Engine::Resume() {
	paused = false;
	timer.Start();
}

int Engine::Loop() {

	game->Init();

	MSG msg = { 0 };

	bool pauseKeyControl = true;

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
			if (pauseKeyControl) {
				if (window->KeyDown(VK_PAUSE)) {
					paused = !paused;
					pauseKeyControl = false;

					if (paused)
						timer.Stop();
					else
						timer.Start();
				}
			}
			else {
				if (window->KeyUp(VK_PAUSE))
					pauseKeyControl = true;
			}

			if (!paused) {
				delta = DeltaTime();

				game->Update();

				graphics->Clear();

				game->Draw();

				graphics->Present();
			}
			else {
				game->onPause();
			}
		}
	} while (msg.message != WM_QUIT);

	game->Finalize();

	return int(msg.wParam);
}

float Engine::DeltaTime() {

#ifdef _DEBUG
	static float totalTime = 0.0f;
	static uint frameCount = 0;
#endif

	delta = timer.Reset();

#ifdef _DEBUG
	totalTime += delta;

	frameCount++;

	if (totalTime >= 1.0f) {
		std::stringstream text;
		text << std::fixed;
		text.precision(3);

		text << window->Title().c_str() << "     " << "FPS: " << frameCount << "    " << "Frame Time: " << delta * 1000 << " (ms)";

		SetWindowText(window->Id(), text.str().c_str());

		frameCount = 0;
		totalTime -= 1.0f;
	}
#endif

	return delta;
}
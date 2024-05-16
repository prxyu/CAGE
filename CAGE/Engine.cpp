#include "Engine.h"
#include "Graphics.h"
#include <Windows.h>
#include <sstream>

Game* Engine::game = nullptr;
Window* Engine::window = nullptr;
Graphics* Engine::graphics = nullptr;

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

	return Loop();
}

int Engine::Loop() {

	game->Init();

	MSG msg = { 0 };

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			game->Update();

			graphics->Clear();

			game->Draw();

			graphics->Present();

			Sleep(16);
		}
	} while (msg.message != WM_QUIT);

	game->Finalize();

	return int(msg.wParam);
}
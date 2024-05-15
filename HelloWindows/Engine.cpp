#include "Engine.h"
#include <Windows.h>
#include <sstream>

Game* Engine::game = nullptr;
Window* Engine::window = nullptr;

Engine::Engine() {
	window = new Window();
}

Engine::~Engine() {
	delete game;
	delete window;
}

int Engine::Start(Game* level) {
	game = level;

	window->Create();

	return Loop();
}

int Engine::Loop() {

	MSG msg = { 0 };
	HDC hdc;
	RECT rect;

	hdc = GetDC(window->Id());

	GetClientRect(window->Id(), &rect);

	game->Init();

	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			game->Update();

			FillRect(hdc, &rect, CreateSolidBrush(window->Color()));

			game->Draw();

			Sleep(16);
		} 

	} while (msg.message != WM_QUIT);

	game->Finalize();

	ReleaseDC(window->Id(), hdc);

	return int(msg.wParam);

}
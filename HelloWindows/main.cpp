#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include <sstream>

class Main : public Game {
private:
	std::stringstream textSize;
	std::stringstream textMode;
	std::stringstream textMouse;
	HDC hdc;
public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

void Main::Init() {
	textSize << "Tamanho: " << window->Width() << " x " << window->Height();
	textMode << "Formato: " << (window->Mode() == WINDOWED ? "Em Janela" : "Tela Cheia");

	hdc = GetDC(window->Id());
}

void Main::Update() {

	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	textMouse.str("");
	textMouse << window->MouseX() << " x " << window->MouseY();

	MoveToEx(hdc, (int) window->CenterX(), (int) window->CenterY(), NULL);
}

void Main::Draw() {
	window->Print("CAGE Prototype", 10, 10, RGB(0, 0, 0));
	window->Print(textSize.str(), 120, 10, RGB(0, 0, 0));
	window->Print(textMode.str(), 270, 10, RGB(0, 0, 0));
	window->Print(textMouse.str(), 420, 10, RGB(0, 0, 0));

	LineTo(hdc, window->MouseX(), window->MouseY());
}

void Main::Finalize() {
	ReleaseDC(window->Id(), hdc);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	Engine* engine = new Engine();
	engine->window->Mode(WINDOWED);
	engine->window->Size(800, 600);
	engine->window->Color(240, 240, 140);
	engine->window->Title("CAGE");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	engine->Start(new Main());
}
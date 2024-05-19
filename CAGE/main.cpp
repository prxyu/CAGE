#include "Resources.h"
#include "Engine.h"
#include "Game.h"

class CAGE : public Game {
private:
	
public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

void CAGE::Init() {

}

void CAGE::Update() {
	if (window->KeyDown(VK_ESCAPE))
		window->Close();
}

void CAGE::Draw() {
	
}

void CAGE::Finalize() {

}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	Engine* engine = new Engine();

	engine->window->Mode(WINDOWED);
	engine->window->Size(940, 540);
	/*engine->graphics->VSync(true);*/
	engine->window->Color(10, 10, 10);
	engine->window->Title("CAGE");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	int status = engine->Start(new CAGE());

	delete engine;
	return status;
}
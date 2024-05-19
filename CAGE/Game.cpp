#include "Game.h"
#include "Engine.h"

Window*& Game::window = Engine::window;

Game::Game() {

}

Game::~Game() {

}

void Game::onPause() {
	Sleep(10);
}
// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

//#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/GameMap.h"
#include "../components/Movimiento.h"
#include "../components/Health.h"
#include "../components/PointOnImage.h"

#include "../game/PlayState.h"

Game::Game() {
}

Game::~Game() { //revisar
	delete stateMachine;
}

void Game::init() {

	//mngr_.reset(new Manager());
	SDLUtils::init("PaintLess", 1920, 1080, "resources/config/resources.json");
	stateMachine = new GameStateMachine();
	stateMachine->pushState(new MainMenuState(stateMachine));
	
	//stateMachine->pushState(new PlayState(stateMachine)); para que inicie el juego sin el menu
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().quitEvent()) {
			exit = true;
			continue;
		}
		if (stateMachine->initChanged()) stateMachine->initState();

		stateMachine->update();
		stateMachine->refresh();
		
		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}
}
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameState.h"
#include "GameStateMachine.h"

GameState::GameState(GameStateMachine* gsm) {
	mngr_.reset(new Manager());
	gameStateMachine = gsm;
}

GameState::~GameState() {}

void GameState::update() { //run
	mngr_->update();
	mngr_->refresh();

	sdlutils().clearRenderer();
	mngr_->render();
	sdlutils().presentRenderer();
}

void GameState::init() {

}
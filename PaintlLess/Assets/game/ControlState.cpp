#include "ControlState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"
#include "../components/Image.h"
#include "../components/Transform.h"

ControlState::ControlState(GameStateMachine* gsm, Texture* desc, bool playState) : GameState(gsm) {
	desc_ = desc;
	playState_ = playState;
	timer_ = 0;
}

void ControlState::init() {
	SDL_Rect dest;
	dest.x = sdlutils().width() / 2 - width / 2;
	dest.y = sdlutils().height() / 2 - height / 2;
	dest.w = width;
	dest.h = height;
	desc_->render(dest);
	if (!playState_) {
		dest.x = sdlutils().width() - 125;
		dest.y = 0;
		dest.w = 125;
		dest.h = 125;
		tr_ = Vector2D(dest.x, dest.y);
		sdlutils().images().at("botonAtras").render(dest);
	}
	sdlutils().presentRenderer();
}

void ControlState::update() {
	if (ih().mouseButtonEvent()) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (ih().getMouseButtonState(ih().LEFT) && mX > tr_.getX() && mX < tr_.getX() + 150 && mY > tr_.getY() && mY < tr_.getY() + 150) {
			gameStateMachine->popState();
		}
	}
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE))
		gameStateMachine->popState();
}

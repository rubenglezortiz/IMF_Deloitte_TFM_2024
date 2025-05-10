#include "DescriptionState.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"

DescriptionState::DescriptionState(GameStateMachine* gsm, Texture* desc) : GameState(gsm) {
	desc_ = desc;
}
void DescriptionState::init() {
	SDL_Rect dest;
	dest.x = sdlutils().width() / 2 - widht / 2;
	dest.y = sdlutils().height() / 2 - height / 2;
	dest.w = widht;
	dest.h = height;
	desc_->render(dest);
	sdlutils().presentRenderer();
}
void DescriptionState::update() {
	if (ih().isKeyDown(SDL_SCANCODE_ESCAPE) || ih().getMouseButtonState(ih().LEFT)) {
		gameStateMachine->popState();
	}
}
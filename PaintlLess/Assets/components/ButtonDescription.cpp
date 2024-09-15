#include "ButtonDescription.h"
#include "../game/DescriptionState.h"
#include "../game/GameStateMachine.h"
#include "../sdlutils/InputHandler.h"

ButtonDescription::ButtonDescription(GameStateMachine* gsm, Texture* desc) : gsm_(gsm), desc_(desc), tr_(nullptr) { }

void ButtonDescription::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ButtonDescription::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().RIGHT)) {
		gsm_->pushState(new DescriptionState(gsm_, desc_));
	}
}
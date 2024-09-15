#include "ButtonSettings.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform2.h"

ButtonSettings::ButtonSettings(GameStateMachine* gsm, CallBackOnClick* cbO) : gsm_(gsm), cbOnClick(cbO) {
	tr_ = nullptr;
}

void ButtonSettings::init() {
	tr_ = entity_->getComponent<Transform2>();
	assert(tr_ != nullptr);
}

void ButtonSettings::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (
		mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT)) {
		cbOnClick(gsm_);
	}
}
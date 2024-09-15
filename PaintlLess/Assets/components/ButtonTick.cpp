#include "ButtonTick.h"
#include "Image.h"
#include "Transform2.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"

ButtonTick::ButtonTick(Texture* tx2, CBOClick* cbo) {
	tx2_ = tx2;
	cbOnClick = cbo;
}

void ButtonTick::init() {
	img_ = entity_->getComponent<Image>();
	tx1_ = img_->getTexture();
	assert(tx1_ != nullptr);
	tr_ = entity_->getComponent<Transform2>();
	assert(tr_ != nullptr);
}

void ButtonTick::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT)){
		selected = !selected;
		cbOnClick(selected);
	}
	if (sdlutils().volumeSFX() > 0) img_->setTexture(tx1_);
	else img_->setTexture(tx2_);
}
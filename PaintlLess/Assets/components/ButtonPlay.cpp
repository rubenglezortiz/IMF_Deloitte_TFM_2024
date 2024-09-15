#include "ButtonPlay.h"

void ButtonPlay::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	img_ = entity_->getComponent<Image>();
	assert(img_ != nullptr);
	tex2_ = img_->getTexture();
	max = gsm_->getCharSel()->getMax();
}

void ButtonPlay::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	contador = gsm_->getCharSel()->getCont();
	if (contador == max && (!gsm_->isOnline() || (gsm_->isOnline() && gsm_->getNetworkManager()->isGameReady()))) {
		img_->setTexture(tex1_);
		if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() && ih().getMouseButtonState(ih().LEFT)) {
			cbOnClick(gsm_);
			sdlutils().soundEffects().at(SONIDO).play();
		}
	}
	else
		img_->setTexture(tex2_);
}

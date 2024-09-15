#include "ButtonSelected.h"
#include "../game/CharacterSelectionState.h"

void ButtonSelected::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	img_ = entity_->getComponent<Image>();
	assert(img_ != nullptr);
	tex2_ = img_->getTexture();
	max = gsm_->getCharSel()->getMax();
}

void ButtonSelected::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	contador = gsm_->getCharSel()->getCont();
	CharacterSelectionState* chst = dynamic_cast<CharacterSelectionState*>(gsm_->currentState());
	if (!selected &&
		mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT) &&
		contador < max) {

		img_->setTexture(tex1_);
		if (chst != nullptr) chst->addCharacterSelected(texM_);
		contador++;
		cbOnClick(gsm_);
		selected = true;
		//sdlutils().soundEffects().at(SONIDO).setChunkVolume(10);
		sdlutils().soundEffects().at(SONIDO).play();
	}
	else if (selected &&
		mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT)) {

		img_->setTexture(tex2_);
		if (chst != nullptr) chst->removeCharacterSelected(texM_);
		contador--;
		cbOnClick(gsm_);
		selected = false;
		//sdlutils().soundEffects().at(DESELECTSONIDO).setChunkVolume(10);
		sdlutils().soundEffects().at(DESELECTSONIDO).play();
		 }
}
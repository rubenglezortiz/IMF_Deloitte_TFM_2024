#include "ButtonCharacterSelection.h"
#include "../game/CharacterSelectionState.h"
#include "../sdlutils/InputHandler.h"

void ButtonCharacterSelection::init() {
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	img_ = entity_->getComponent<Image>();
	assert(img_ != nullptr);
	tex2_ = img_->getTexture();
}

void ButtonCharacterSelection::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT)  && tipo != chst_->getTipo()) {
		sdlutils().soundEffects().at("menuButtonSound").play();
		int x = sdlutils().width() / 2 - (3 * (300 / 2));
		int i = 0;

		chst_->setSelected(true);
		chst_->setTipo(tipo);
		img_->setTexture(tex_);

		if (tipo == 0) {
			int y = sdlutils().height() / 2 - 300;
			for (Entity* e : entity_->getMngr()->getEnteties()) {
				Transform* tr = e->getComponent<Transform>();

				if (e->hasGroup<Defense>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Utility>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Attack>()) {
					tr->setW(300); tr->setH(300);
					tr->getPos().setX(x + i % 3 * tr->getW());
					tr->getPos().setY(y + i / 3 * tr->getH());
					i++;
				}
			}
		}
		else if (tipo == 1) {
			int y = sdlutils().height() / 2 - 150;
			for (Entity* e : entity_->getMngr()->getEnteties()) {
				Transform* tr = e->getComponent<Transform>();

				if (e->hasGroup<Attack>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Utility>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Defense>()) {
					tr->setW(300); tr->setH(300);
					tr->getPos().setX(x + i * tr->getW());
					tr->getPos().setY(y);
					i++;
				}
			}
		}
		else {
			x = sdlutils().width() / 2 - 600;
			int y = sdlutils().height() / 2 - 150;
			for (Entity* e : entity_->getMngr()->getEnteties()) {
				Transform* tr = e->getComponent<Transform>();

				if (e->hasGroup<Attack>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Defense>()) tr->getPos().setX(-300);
				else if (e->hasGroup<Utility>()) {
					tr->setW(300); tr->setH(300);
					tr->getPos().setX(x + i * tr->getW());
					tr->getPos().setY(y);
					i++;
				}
			}
		}
	}
	else if (mX >= tr_->getPos().getX() && mX <= tr_->getW() + tr_->getPos().getX() && mY >= tr_->getPos().getY() && mY <= tr_->getH() + tr_->getPos().getY() &&
		ih().getMouseButtonState(ih().LEFT) && chst_->getSelected()) {
		sdlutils().soundEffects().at("menuButtonSound").play();
		int i = 0;
		int x, y;
		int w = 250;
		int h = 250;
		for (Entity* e : entity_->getMngr()->getEnteties()) {
			if (e->hasComponent<ButtonSelected>()) {
				Transform* tr = e->getComponent<Transform>();
				tr->setW(w); tr->setH(h);
				if (i < 5) {
					x = sdlutils().width() / 2 - 5 * w / 2 + i * w;
					y = 150;
				}
				else if (i < 8) {
					x = sdlutils().width() / 2 - 3 * w / 2 + (i - 5) * w;
					y = 150 + h;
				}
				else {
					x = sdlutils().width() / 2 - 5 * w / 2 + (i - 8) * w;
					y = 150 + 2 * h;
				}
				tr->getPos().setX(x);
				tr->getPos().setY(y);
				i++;
			}
		}
		chst_->setSelected(false);
		chst_->setTipo(-1);
		img_->setTexture(tex2_);
	}
	if (tipo != chst_->getTipo() && chst_->getSelected())
	img_->setTexture(tex2_);
}
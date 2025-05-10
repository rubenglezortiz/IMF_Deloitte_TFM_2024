#include "ButtonHovered.h"

void ButtonHovered::init() {
	img_ = entity_->getComponent<Image>();
	assert(img_ != nullptr);
	tr_ = entity_->getComponent<Transform>();
	assert(tr_ != nullptr);
	tex1_ = img_->getTexture();
}

void ButtonHovered::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	int w = tr_->getW() * 10;
	if (Collisions::collides(Vector2D(mX, mY), 1, 1, tr_->getPos() - Vector2D(w / 2, 0), w, tr_->getH()))
		img_->setTexture(tex2_);
	else img_->setTexture(tex1_);
}
#pragma once

#include "../ecs/Component.h"
#include "Transform.h"
#include "Image.h"
#include "../sdlutils/Texture.h"

class CharacterSelectionState;

class ButtonCharacterSelection : public Component {

private:
	int tipo;
	CharacterSelectionState* chst_;
	Transform* tr_;
	Texture* tex_, *tex2_;
	Image* img_;

public:
	ButtonCharacterSelection(int t, CharacterSelectionState* chst, Texture* tex) : tipo(t), chst_(chst), tex_(tex) {}
	virtual ~ButtonCharacterSelection(){}
	void init() override;
	void update() override;
};
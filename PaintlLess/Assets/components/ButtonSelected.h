#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"
#include "Transform.h"
#include "Image.h"
#include "../utils/Collisions.h"

using CallBackOnClick = void(GameStateMachine* gsm);

class ButtonSelected : public Component {

private:
	Transform* tr_;
	Texture *tex1_, *tex2_, *texM_;
	Image* img_;
	GameStateMachine* gsm_;
	int contador = 0;
	int max = 0;
	bool selected = false;
	const std::string SONIDO = "seleccionSound";
	const std::string DESELECTSONIDO = "menuButtonSound";

protected:
	CallBackOnClick* cbOnClick;

public:
	ButtonSelected(GameStateMachine* gsm, Texture* tex, Texture* texM, CallBackOnClick* cb) : gsm_(gsm), cbOnClick(cb), tex1_(tex), tex2_(nullptr), texM_(texM), tr_(nullptr), img_(nullptr) {}
	virtual ~ButtonSelected() {}
	void init() override;
	void update() override;
};
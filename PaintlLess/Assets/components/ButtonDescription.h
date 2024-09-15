#pragma once

#include "../ecs/Component.h"
#include "Transform.h"
class GameStateMachine;
class Texture;

class ButtonDescription : public Component {
private:
	GameStateMachine* gsm_;
	Texture* desc_;
	Transform* tr_;
	bool select_ = false;

public:
	ButtonDescription(GameStateMachine* gsm, Texture* desc);
	~ButtonDescription(){}
	void init() override;
	void update() override;
};
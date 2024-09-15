#pragma once

#include "../ecs/Component.h"

class GameStateMachine;
class Transform2;

using CallBackOnClick = void(GameStateMachine* gsm);

class ButtonSettings : public Component {
private:
	Transform2* tr_;
	GameStateMachine* gsm_;

protected:
	CallBackOnClick* cbOnClick;

public:
	ButtonSettings(GameStateMachine* gsm, CallBackOnClick* cb);
	~ButtonSettings() {}
	void init() override;
	void update() override;
};
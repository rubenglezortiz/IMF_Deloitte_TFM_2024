#pragma once

#include "../ecs/Component.h"

class GameStateMachine;
class Image;
class Texture;
class Transform2;

using CBOClick = void(bool state);

class ButtonTick : public Component {

private:
	Image* img_;
	Transform2 *tr_;
	Texture *tx1_, *tx2_;
	bool selected = false;

protected:
	CBOClick* cbOnClick;

public:

	ButtonTick(Texture *tx2, CBOClick* cbo);
	~ButtonTick(){}
	void init() override;
	void update() override;
};
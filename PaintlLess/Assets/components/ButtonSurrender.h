#pragma once


#include "../ecs/Component.h"

class PlayState;
class Transform2;
class ButtonSurrender : public Component {
private:
	Transform2* tr_;
	PlayState* pst_;
public:
	ButtonSurrender(PlayState* ps);
	~ButtonSurrender(){}
	void init() override;
	void update() override;
};
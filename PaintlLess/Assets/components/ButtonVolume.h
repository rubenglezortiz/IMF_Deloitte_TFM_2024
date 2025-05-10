#pragma once

#include "../ecs/Component.h"
#include "../game/SoundManager.h"
class Transform2;

class ButtonVolume : public Component {
private:
	bool pulse_ = false;
	bool music = false;
	int volume_ = 0;
	Transform2* tr_ = nullptr;
public:
	ButtonVolume(bool musica) : music(musica) {}
	virtual ~ButtonVolume(){}
	void init() override;
	void update() override;
};
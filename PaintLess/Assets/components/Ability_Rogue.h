#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Ability_Rogue : public Component {
public:
	Ability_Rogue(){}
	~Ability_Rogue(){}
	int ataqueCritico();
};
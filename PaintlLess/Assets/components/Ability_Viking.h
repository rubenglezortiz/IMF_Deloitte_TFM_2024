#pragma once

#include "./Ability.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"
#include "./FramedImage.h"
#include "../game/AbilityStruct.h"

class Ability_Viking : public AbilityStruct {
public:
	Ability_Viking();
	virtual bool AbilityExecute(int x, int y) override;
	virtual ~Ability_Viking() {}
};

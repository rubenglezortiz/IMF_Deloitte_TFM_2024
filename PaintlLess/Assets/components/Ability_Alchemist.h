#pragma once

#include "Ability.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Health.h"
#include "./Movimiento.h"

class Ability_Alchemist : public AbilityStruct
{
public:
	Ability_Alchemist();
	virtual bool AbilityExecute(int x, int y) override;
	virtual ~Ability_Alchemist() {};
};
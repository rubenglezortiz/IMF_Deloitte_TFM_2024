#pragma once

#include "./Ability.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Movimiento.h"
#include "../game/AbilityStruct.h"

struct Ability_Kirin : public AbilityStruct {
public:
	Ability_Kirin();
	virtual bool AbilityExecute(int x, int y) override;
	virtual ~Ability_Kirin() {}
};
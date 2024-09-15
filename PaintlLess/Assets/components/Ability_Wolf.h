#pragma once

#include "../ecs/Component.h"
#include "../game/AbilityStruct.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"

class Ability_Wolf : public AbilityStruct {
public:
	Ability_Wolf();
	virtual ~Ability_Wolf() {}
	virtual bool AbilityExecute(int x, int y) override;
};


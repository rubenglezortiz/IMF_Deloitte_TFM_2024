#pragma once

#include "./Ability.h"
#include "../sdlutils/InputHandler.h"
#include "../game/OffsetInfo.h"
#include "Movimiento.h"
#include "Health.h"
#include "../game/AbilityStruct.h"

struct Ability_Architect : AbilityStruct {
public:
	Ability_Architect();
	virtual bool AbilityExecute(int x, int y) override;
	virtual ~Ability_Architect() {  }
};

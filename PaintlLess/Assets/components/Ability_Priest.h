#pragma once

#include "Ability.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "GameMap.h"
#include "Health.h"
#include "../game/AbilityStruct.h"

#include <vector>

class Ability_Priest : public AbilityStruct {
public:
	Ability_Priest();
	virtual ~Ability_Priest() {}
	virtual bool AbilityExecute(int x, int y) override;
};
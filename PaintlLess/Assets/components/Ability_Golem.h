#pragma once

#include "./Ability.h"
#include "../game/AbilityStruct.h"
#include "../ecs/Entity.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"
#include "GameMap.h"

class Ability_Golem : public AbilityStruct {
public:
    Ability_Golem();
    virtual void OnDie() override;
    ~Ability_Golem() {};
};
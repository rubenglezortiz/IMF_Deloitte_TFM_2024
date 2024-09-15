#pragma once

#include "../game/AbilityStruct.h"
#include "Health.h"
#include "Image.h"
#include "Transform.h"
#include "Movimiento.h"

class Ability_Bomb : public AbilityStruct { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Bomb();
    virtual void OnDie() override;
    virtual void OnCross() override;
    void explode();
    virtual ~Ability_Bomb() {}
private:
    const std::vector<Vector2D> casillas{ {0, -1}, {-1, -1}, {1, -1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1} };
};

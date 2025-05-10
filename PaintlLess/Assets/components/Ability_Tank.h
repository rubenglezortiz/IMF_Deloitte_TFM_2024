#pragma once

#include "../ecs/Component.h"
#include "../game//AbilityStruct.h"
#include "Health.h"

class Ability_Tank : public AbilityStruct { //lleva este componente la destrucci�n del objeto??
public:
    Ability_Tank();
    virtual ~Ability_Tank() {}
    virtual void initiliceData(Ability* ab) override;
    virtual void finTurno() override;
private:
    Health* mLive;
    int turnos;
    int mTurno;
    int lives;
};

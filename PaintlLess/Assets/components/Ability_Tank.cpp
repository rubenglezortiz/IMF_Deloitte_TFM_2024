#include "Ability_Tank.h"
#include "../ecs/Entity.h"

Ability_Tank::Ability_Tank() : lives(0), mTurno(0), turnos(3){}

void Ability_Tank::initiliceData(Ability* ab)
{
	AbilityStruct::initiliceData(ab);
	Entity* entity_ = this->getAbility()->getEntity();
	mLive = entity_->getComponent<Health>();
	lives = mLive->getLives();
	mTurno = turnos;
}

void Ability_Tank::finTurno() {

	Entity* entity_ = this->getAbility()->getEntity();

	if (mLive->getLives() < lives) {
		if (mTurno == 0) {
			mLive->heal();
			mTurno = turnos;
		}
		else {
			mTurno--;
		}
	}
	else
		mTurno = turnos;
}
#include "Ability_Creeper.h"

void Ability_Creeper::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
}

void Ability_Creeper::finTurno()
{
	lifeCreeper -= 1;
	if (lifeCreeper < 0) {
		mapa->setCreeper(mapa->SDLPointToMapCoords(tr_->getPos()),false);
		entity_->setActive(false);
	}
	else {
		auto* e = mapa->getCharacter(mapa->SDLPointToMapCoords(tr_->getPos()));			// E.Rojo == 0 - E.Azul == 1
		if (e == nullptr) return;
		if ((equip == 0 && e->hasGroup<Equipo_Azul>()) || (equip == 1 && e->hasGroup<Equipo_Rojo>())) {
			e->getComponent<Health>()->hit(1);
			//sdlutils().soundEffects().at("enredaderasSound").setChunkVolume(5);
			sdlutils().soundEffects().at("enredaderasSound").play(); //-----------------------------------------------------------		
		}
	}
}
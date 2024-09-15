#include "DieAfterXTurns.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "Movimiento.h"
#include "Attack.h"

void DieAfterXTurns::finTurno()
{
	turnsToDie--;
	if (turnsToDie <= 0)
	{
		Movimiento* mov = this->entity_->getComponent<Movimiento>();
		Attack* at = this->entity_->getComponent<Attack>();
		if (mov != nullptr) mov->finTurno();
		if (at != nullptr) at->finTurno();
		mapa->removeCharacter(mapa->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos())); //Quitar la entidad muerta	
		this->entity_->getComponent<FramedImage>()->setAnim(DeathA, true);
	}
}
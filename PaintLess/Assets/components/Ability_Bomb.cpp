#include "Ability_Bomb.h"

Ability_Bomb::Ability_Bomb() {}

void Ability_Bomb::OnDie()
{
	explode();
}

void Ability_Bomb::OnCross()
{
	Health::kill(this->getAbility()->getMap(), this->getAbility()->getEntity());
}

void Ability_Bomb::explode()
{
	Entity* entity_ = this->getAbility()->getEntity();
	Vector2D posBomb = entity_->getComponent<Transform>()->getPos();
	GameMap* mapa = this->getAbility()->getMap();
	Color color = entity_->hasGroup<Equipo_Azul>() ? Azul : Rojo;
	Health* health;

	posBomb = mapa->SDLPointToMapCoords(posBomb);

	//FALTA QUE EXPLOTE AL PISAR AREA ENEMIGA -------------------------------------------------------------------------
	for (int i = 0; i < casillas.size(); i++) {
		//Hay personajes ==> Daño
		if (mapa->casillaValida(casillas[i] + posBomb) && mapa->getCharacter(casillas[i] + posBomb) != nullptr && mapa->esPintable(casillas[i] + posBomb)) {
			auto character = mapa->getCharacter(casillas[i] + posBomb);
			if ((character->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Rojo>()) || (character->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Azul>()))
			{
				health = character->getComponent<Health>();
				if (health != nullptr) health->hit(1);
			}
		}
		//Es pintable ==> Pinta
		if (mapa->movimientoPosible(casillas[i] + posBomb)) {
			mapa->setColor(casillas[i] + posBomb, color);
		}
	}
	//sdlutils().soundEffects().at("bombaSound").setChunkVolume(50);
	sdlutils().soundEffects().at("bombaSound").play(); //-----------------------------------------------------------	
}

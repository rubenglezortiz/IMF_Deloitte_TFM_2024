#include "Ability_Skeleton.h"
#include "DieAfterXTurns.h"

Ability_Skeleton::Ability_Skeleton(int lv) : livesOfGeneratedSkeleton(lv) { }

void Ability_Skeleton::OnDie()
{
	GameMap* mapa_ = this->getAbility()->getMap();
	Entity* self = this->getAbility()->getEntity();
	Transform* selfTransform = self->getComponent<Transform>();
	Vector2D selfPos = mapa_->SDLPointToMapCoords(selfTransform->getPos());

	//Generate an skeleton that dies in 2 turns and it invincible
	Entity* generatedSkeleton = self->getMngr()->addEntity(RenderLayer::Tablero3);
	generatedSkeleton->setGroup<Personajes>(generatedSkeleton);
	generatedSkeleton->addComponent<Transform>(
		selfPos,        //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	bool isBlue = self->hasGroup<Equipo_Azul>();
	if (isBlue)
		generatedSkeleton->setGroup<Equipo_Azul>(generatedSkeleton);
	else 
		generatedSkeleton->setGroup<Equipo_Rojo>(generatedSkeleton);
	
	FramedImage* generatedSklFramedImage;
	generatedSklFramedImage = generatedSkeleton->addComponent<FramedImage>(&sdlutils().images().at(isBlue ? "esqueletoSheetRD" : "esqueletoSheetAD"), 150, Unit::Esqueleto, false, true);
	generatedSklFramedImage->setAnim(DeathA);
	generatedSkeleton->addComponent<Attack>(mapa_->getPlayState(), 1, 1, 0);
	generatedSkeleton->addComponent<Movimiento>(mapa_->getPlayState(), 1);
	generatedSkeleton->addComponent<DieAfterXTurns>(2, mapa_);
	mapa_->setCharacter(selfPos, generatedSkeleton);
}
#include "Ability_Alchemist.h"

Ability_Alchemist::Ability_Alchemist() : AbilityStruct(selectorA, ShaderForm::Cross, ShaderType::AttackSh) {}

bool Ability_Alchemist::AbilityExecute(int x, int y)
{
	GameMap* map = this->getAbility()->getMap();
	Entity* entity_ = this->getAbility()->getEntity();
	if (map->getCharacter(Vector2D(x, y))->hasComponent<Movimiento>() && map->esPintable(Vector2D(x, y))) {
		entity_->getComponent<FramedImage>()->setAnim(A_A_A);
		map->getCharacter(Vector2D(x, y))->getComponent<Movimiento>()->setStun(2);
		sdlutils().soundEffects().at("alquimistaSound").play(); //-----------------------------------------------------------	
	}
	sdlutils().soundEffects().at("alquimistaSound").setChunkVolume(30);
	return true;
}

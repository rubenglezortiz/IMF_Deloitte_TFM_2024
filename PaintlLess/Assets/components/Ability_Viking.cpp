#include "Ability_Viking.h"

Ability_Viking::Ability_Viking() : AbilityStruct(selectorA, ShaderForm::VikingForm, ShaderType::nullSh) 
{
}

bool Ability_Viking::AbilityExecute(int x, int y)
{
	GameMap* map = this->getAbility()->getMap();
	Entity* entity_ = this->getAbility()->getEntity();
	Entity* enemie = map->getCharacter(Vector2D(x, y));
	if (enemie == nullptr) return false;
	Health* vida = enemie->getComponent<Health>();
	if(vida != nullptr) vida->hit(1);
	//sdlutils().soundEffects().at("vikingoSound").setChunkVolume(30);
	sdlutils().soundEffects().at("vikingoSound").play(); //-----------------------------------------------------------	
	entity_->getComponent<FramedImage>()->setAnim(A_A_A);
	return true;
}

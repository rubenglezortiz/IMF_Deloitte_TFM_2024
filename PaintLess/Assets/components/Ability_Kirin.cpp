#include "Ability_Kirin.h"

Ability_Kirin::Ability_Kirin() : AbilityStruct(selector, ShaderForm::Cross, ShaderType::KirinSh, 2){ }

bool Ability_Kirin::AbilityExecute(int x, int y)
{
	GameMap* map = this->getAbility()->getMap();
	Entity* entity_ = this->getAbility()->getEntity();

	auto& pos = entity_->getComponent<Transform>()->getPos();
	map->removeCharacter(map->SDLPointToMapCoords(pos));
	pos.setX(x * map->getCellWidth() + OFFSET_X);
	pos.setY(y * map->getCellHeight() + OFFSET_Y + OFFSET_TOP);
	map->setCharacter(map->SDLPointToMapCoords(pos), entity_);
	Color color = entity_->hasGroup<Equipo_Azul>() ? Azul : Rojo;
	map->setColor(map->SDLPointToMapCoords(pos), color);
	//sdlutils().soundEffects().at("kirinSound").setChunkVolume(5);
	sdlutils().soundEffects().at("kirinSound").play();
	return true;
}

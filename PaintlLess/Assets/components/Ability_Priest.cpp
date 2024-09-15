#include "Ability_Priest.h"

Ability_Priest::Ability_Priest() : AbilityStruct(selectorH, ShaderForm::TxT, ShaderType::nullSh) {}

bool Ability_Priest::AbilityExecute(int x, int y)
{
	bool hasCured = false;
	GameMap* map = this->getAbility()->getMap();
	Entity* entity_ = this->getAbility()->getEntity();
	std::vector<Vector2D> abilityCells = this->getAbility()->getCells();
	if (abilityCells.empty()) {
		this->getAbility()->Shade();
		abilityCells = this->getAbility()->getCells();
	}
	for (int i = 0; i < abilityCells.size(); i++) {
		if (map->getCharacter(abilityCells[i]) != nullptr) {
				if ((map->getCharacter(abilityCells[i])->hasGroup<Equipo_Azul>() && entity_->hasGroup<Equipo_Azul>()) || (map->getCharacter(abilityCells[i])->hasGroup<Equipo_Rojo>() && entity_->hasGroup<Equipo_Rojo>())) {
					map->getCharacter(abilityCells[i])->getComponent<Health>()->healMonaguillo(1);
					entity_->getComponent<FramedImage>()->setAnim(A_A_A);
					sdlutils().soundEffects().at("monaguilloSound").play();
					hasCured = true;
				}
		}
	}
	return hasCured;
}

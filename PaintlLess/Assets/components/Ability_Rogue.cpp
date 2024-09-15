#include "Ability_Rogue.h"

int Ability_Rogue::ataqueCritico() {
	if (sdlutils().rand().nextInt(1, 5) <= 3)
		return 2;
	else return 4;
}
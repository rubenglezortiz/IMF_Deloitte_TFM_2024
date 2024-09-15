#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"

#include "Health.h"

class PlayState;
class Ability_Creeper : public Component {
private:	
	GameMap* mapa;	
	Transform* tr_;
	int lifeCreeper; //los turnos que aguanta
	int equip;

public:
	Ability_Creeper(int e) : mapa(nullptr), tr_(nullptr), lifeCreeper(2), equip(e){}
	~Ability_Creeper() {}

	void init() override;
	void finTurno() override;
};
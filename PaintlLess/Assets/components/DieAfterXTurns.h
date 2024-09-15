#pragma once
#include "../ecs/Component.h"
#include "GameMap.h"

class DieAfterXTurns : public Component
{
public:
	DieAfterXTurns(int&& turnsToDie, GameMap* mapa) : turnsToDie(turnsToDie), mapa(mapa) {};
	virtual void finTurno();
private:
	int turnsToDie;
	GameMap* mapa;
};
#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "Transform2.h"
#include "Image.h"

class PlayState;
class GameStateMachine;
class Interfaz : public Component {
private:
	PlayState* playState;
	SDL_Rect destNum, destMana, destAcciones, destEnergy, destBarraTurnos, destTurnos, destNumTurnos, destBarraPorcentajes, destPorcentaje1, destPorcentaje2, destOpciones, destPorcentaje,
		numPorcA, numPorcR;
	Texture *texEnergy, *texTurno;
	GameStateMachine* gsm_;
	int numCasillasPintables, casAzul, casRojo;
public:
	Interfaz(){}
	virtual ~Interfaz(){}
	void init() override;
	void render() override;
	static void menuOpciones(GameStateMachine* gsm);
};
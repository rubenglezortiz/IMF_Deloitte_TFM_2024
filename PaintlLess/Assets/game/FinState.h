#pragma once

#include "GameState.h"

class GameStateMachine;

class FinState : public GameState {
private:
	int equipo, porcentaje;
	const int  WIDTH = 1920;
	const int  HEIGHT = 1080;
	const int w = 310;
	const int h = 150;
public:
	FinState(GameStateMachine* gsm, int equipo, int porcentaje);
	~FinState() {}
	void init() override;
	void update() override;
	//Callbacks
	static void exitMenu(GameStateMachine* gsm);
};
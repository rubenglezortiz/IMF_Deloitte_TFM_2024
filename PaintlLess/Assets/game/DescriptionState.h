#pragma once

#include "GameState.h"

class GameStateMachine; 
class Texture;

class DescriptionState : public GameState {
private:
	const int widht = 700;
	const int height = 1000;
	Texture* desc_;
public:
	DescriptionState(GameStateMachine* gsm, Texture* desc);
	~DescriptionState() {}
	void update() override;
	void init() override;
};
#pragma once

#include "GameState.h"
#include "../sdlutils/SDLUtils.h"

class GameStateMachine;
class Texture;
class Transform;

class ControlState : public GameState {
private:
	const int width = sdlutils().width();
	const int height = sdlutils().height();

	Texture* desc_;
	Vector2D tr_;
	bool playState_;
	int timer_;
public:
	ControlState(GameStateMachine* gsm, Texture* desc, bool playState);
	~ControlState() {}
	void init() override;
	void update() override;

};
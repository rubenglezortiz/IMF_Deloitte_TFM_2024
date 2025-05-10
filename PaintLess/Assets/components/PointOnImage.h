#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "GameMap.h"
#include "../sdlutils/InputHandler.h"
#include "../game/LerpingFunctions.h"
#include "../game/OffsetInfo.h"
#include "../../checkML.h"

class PointOnImage : public Component {
public:
	PointOnImage(Texture* tex) : tex_(tex), mapa(nullptr), resultado(0), src_(SDL_Rect())  {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		dest.x = mX + OFFSET_X;
		dest.y = mY + OFFSET_Y + OFFSET_TOP;
		dest.h = tex_->height();
		dest.w = tex_->width();
	}

	virtual ~PointOnImage() {
	}

	void init() override;
	void update() override;
	void render() override { tex_->render(dest); }


private:
	SDL_Rect dest;
	GameMap* mapa;
	int resultado;

	Vector2D position;
	Texture* tex_;
	SDL_Rect src_;

	//Animation
	Vector2D currentPosition;
	Vector2D lastPosition;
	float lerpTime = 0;
};
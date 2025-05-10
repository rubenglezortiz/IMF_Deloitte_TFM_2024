#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../game/values.h"


class FramedImage : public Component {
public:
	
	FramedImage(Texture* tex,  int d, Unit personaje, bool orden = false, bool muerto = false);
	virtual ~FramedImage() {}
	void init() override;
	void render() override;
	void setAnim(UnitAnim ua, bool orden = false);
	void update() override;
	void renderStun() ;

private:
	Unit personaje;
	Transform* tr_;
	Texture* tex_;
	SDL_Rect src_;
	Vector2D iniFrame, endFrame;
	Uint32 time;
	UnitAnim currentAnim = IdleA;
	int delay;
	int delayAux;
	int rows_, cols_;	 // number of rows & cols in the texture
	int w_, h_;			 // width & height of the texture
	int r_, c_;			 // row & col to render
	bool order = false;
	bool muertos = false;

	Vector2D lastPosition = { 0, 0 };
	Vector2D interpolatedTf;
	float lerpTime = 1;

	//Stun
	Texture* tex_stun;
	SDL_Rect src_stun;
	Uint32 time_stun;
	int w_stun, h_stun;
	int r_stun, c_stun;
};
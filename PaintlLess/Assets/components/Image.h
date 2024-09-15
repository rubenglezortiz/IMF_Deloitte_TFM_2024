// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
#include "./Transform2.h"

class Image : public Component {
public:
	Image(Texture* tex) :
		tr_(nullptr), //
		tex_(tex), //
		currFrame(0)

	{
		src_ = { 0, 0, tex->width(), tex->height() };
	}

	Image(Texture* tex, SDL_Rect src) :
		tr_(nullptr), //
		tr2_(nullptr),
		tex_(tex), //
		src_(src)

	{
		currFrame = src.x * src.w;
	}

	Image(Texture* tex, int rows, int cols, int r, int c) :
		tr_(nullptr), tr2_(nullptr),
		tex_(tex) //
	{
		auto w = tex->width() / cols;
		auto h = tex->height() / rows;
		src_ = { w * c, h * r, w, h };
		currFrame = c * w;
	}


	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		if (tr_ == nullptr) {
			tr2_ = entity_->getComponent<Transform2>();
			assert(tr2_ != nullptr);
		} else
			assert(tr_ != nullptr);
	}

	void render() override;

	void shiny();

	void dark();

	void setTexture(Texture* tex) { tex_ = tex; }

	Texture* getTexture() { return tex_; }

private:
	Transform* tr_;
	Transform2* tr2_;
	Texture* tex_;
	SDL_Rect src_;
	int currFrame;
};


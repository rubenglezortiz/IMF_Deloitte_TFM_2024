#pragma once

#include "../ecs/Component.h"
#include "../utils/Collisions.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "Image.h"

class ButtonHovered : public Component {
private:
	Image* img_;
	Transform* tr_;
	Texture* tex1_;
	Texture* tex2_;

public:
	ButtonHovered(Texture* tex) : tex2_(tex), tr_(nullptr), tex1_(nullptr) {}
	virtual ~ButtonHovered() {}
	void init() override;
	void update() override;
};

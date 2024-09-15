#include "../ecs/Component.h"
#include "Transform.h"
#include "Image.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"

using CallBackOnClick = void(GameStateMachine* gsm);

class ButtonPlay : public Component {
private:
	Transform* tr_;
	MenuButton* bt_;
	Texture* tex1_;
	Texture* tex2_;
	Image* img_;
	GameStateMachine* gsm_;
	int contador = 0;
	int max = 0;
	bool selected = false;
	const std::string SONIDO = "seleccionSound";

protected:
	CallBackOnClick* cbOnClick;

public:
	ButtonPlay(GameStateMachine* gsm, Texture* tex, CallBackOnClick* cb) : gsm_(gsm), cbOnClick(cb), tex1_(tex), tex2_(nullptr), tr_(nullptr), bt_(nullptr), img_(nullptr) {}
	virtual ~ButtonPlay() {}
	void init() override;
	void update() override;
};

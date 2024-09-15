#pragma once

#include "../ecs/Component.h"
#include "../../Assets/utils/Vector2D.h"
#include "../../Assets/sdlutils/InputHandler.h"
#include "Transform.h"
#include <string>

using namespace std;
class GameStateMachine;

using CallBackOnClick = void(GameStateMachine* gsm);

class MenuButton : public Component {
private:
	GameStateMachine* gsm_;
	Transform* tr_;
	bool selected = false;
	string SONIDO = "menuButtonSound";//"menuInicioSound";//"seleccionSound"; //"continueSound";//
	
protected:
	CallBackOnClick* cbOnClick;

public:
	MenuButton(GameStateMachine* gsm, CallBackOnClick* cb);
	MenuButton(GameStateMachine* gsm, CallBackOnClick* cb, string sonido);
	virtual ~MenuButton() {};
	virtual void update();
	void init() override;
	bool select() { return selected; }
	GameStateMachine* getGSM() { return gsm_; }
};
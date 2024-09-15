#pragma once

#include <stack>
#include "GameState.h"
#include "../../CharactersSelected.h"
#include "Network.h"
class PlayState;
//#include "checkML.h"

using namespace std;

class GameStateMachine {
private:
	stack<GameState*> states;    // Pila de estados.
	CharactersSelected* charSel; // Vector de personajes.
	Network* net;
	PlayState* playState;
	bool initChangedState;
	GameState* lastChanged;
	uint popState_ = 0;
	bool online = false;
public:
	// Constructora.
	GameStateMachine() : lastChanged(nullptr), initChangedState(false) { charSel = new CharactersSelected();  net = new Network(); };
	// Destructora.
	~GameStateMachine();

	bool initChanged() { return initChangedState; };
	void initOnline();

	void initState();
	void update();
	void setOnline(bool a) { online = a; };
	bool isOnline() { return online; }
	void refresh();
	int getSize() { return states.size(); }
	void restartCharacterSelection();
	Network* getNetworkManager() { return net; }

	// Devuelve el estado actual.
	GameState* currentState() { return states.top(); };
	// Saca estado de la pila.
	void popState();
	// Introduce estado en la pila.
	void pushState(GameState* state);
	// Cambio de estado.
	void changeState(GameState* state);
	// Devuelve el puntero a CharactersSelected.
	CharactersSelected* &getCharSel() { return charSel; };

	void setPlayState(PlayState* playState);
	PlayState* getPlayState();
};
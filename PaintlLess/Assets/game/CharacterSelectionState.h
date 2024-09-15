#pragma once
#include "GameState.h"
#include "Values.h"
#include "../sdlutils/Texture.h"
#include "../../CharactersSelected.h"
#include <vector>
#include "../../checkML.h"

class GameStateMachine;
class Manager;
using namespace std;

/*
* CharacterSelectionState maneja el menú de selección de personajes.
*/

class CharacterSelectionState : public GameState 
{
private:
	// Constantes para el ancho y alto de los sprites de los personajes.
	 const int w = 250;
	 const int h = 250;
	 const int offsetY = 150;
	 bool selected = false;
	 int tipo = -1;
	 vector<Texture*> personajesSelected;
	 std::string equipo;
	 bool enemyHasSelected = false;
	 bool selfHasSelected = false;
	// Método que renderiza los personajes seleccionados en el mazo.
	 void renderSelected();

public:
	// Cargamos los botones de los personajes.
	 CharacterSelectionState(GameStateMachine* gsm);
	 ~CharacterSelectionState();

	// Método que carga la partida.
	 static void play(GameStateMachine* gsm);

	// Update que renderiza el estado.
	 void update() override;
	
	 void setTipo(int n) { tipo = n; }
	 int getTipo() { return tipo; }
	 void setSelected(bool t) { selected = t; }
	 bool getSelected() { return selected;  }
	 void setEnemySelected() { enemyHasSelected = true; }
	 void setSelfHasSelected() { selfHasSelected = true; }

	 bool getEnemySelected() { return enemyHasSelected; }
	 bool getSelfSelectd() { return selfHasSelected; }
	 void checkGameReady(GameStateMachine* gsm);

	// Métodos para seleccionar a los personajes.
	 static void updateAlquimista(GameStateMachine* gsm);
	 static void updateArquitecta(GameStateMachine* gsm);
	 static void updateBomba(GameStateMachine* gsm);
	 static void updateCazador(GameStateMachine* gsm);
	 static void updateDruida(GameStateMachine* gsm);
	 static void updateEsqueleto(GameStateMachine* gsm);
	 static void updateGolem(GameStateMachine* gsm);
	 static void updateKirin(GameStateMachine* gsm);
	 static void updateLobo(GameStateMachine* gsm);
	 static void updateMonaguillo(GameStateMachine* gsm);
	 static void updatePicara(GameStateMachine* gsm);
	 static void updateTanque(GameStateMachine* gsm);
	 static void updateVikingo(GameStateMachine* gsm);

	// Métodos que añaden/restan personajes seleccionados del mazo.
	 void addCharacterSelected(Texture* tex);
	 void removeCharacterSelected(Texture* tex);
};
#pragma once
#include "GameState.h"
#include <vector>
#include "../components/UniversalShader.h"

class EntityFactory;
class Network;

using namespace std;

/*
* PlayState maneja la partida en curso.
*/

enum Equipo { Primero, Segundo };
class GameMap;
class Vector2D;
class PlayState : public GameState
{

private:
	const int MAX_TURNOS = 10;
	const int MAX_ACCIONES = 5;
	const int MAX_MANA = 10;
	const int INCREMENTO_MANA = 2;
	int mana_1 = 10;
	int mana_2 = 10;
	int accionesPorTurno = MAX_ACCIONES, turnosActuales = 1;
	int mana;
	int pintado_1, pintado_2;
	std::string music;
	Equipo jugadorActual = Segundo;
	vector<bool> ch1, ch2;
	GameMap* mapa_;
	Network* net;
	Entity* shaderManager;
	UniversalShader* abililyShader;
	UniversalShader* movementShader;
	UniversalShader* attackShader;
public:

	// Constructora.
	PlayState(GameStateMachine* gsm, vector<bool> charss, vector<bool> charss2, int mapa, int tileset);
	// Destructora.
	virtual ~PlayState();

	// Método que crea el mazo.
	void createMazo(int n, int x, int equipo);
	void mazoEquipo();
	void moveMazo();
	void update() override;
	void _net_moveChar(Vector2D charPosInMap, Vector2D dest);
	void _net_abilityChar(Vector2D charPosInMap, Vector2D dest);
	void _net_attackChar(Vector2D charPosInMap, Vector2D dest, int dmg);
	void _net_endGame();

	void CheckPasarTurno();

	GameMap* getMapa() { return mapa_; }

	void pasaTurno();
	void checkEndGame();
	Equipo getTurno() const { return jugadorActual; }

	PlayState* getPlayState() { return this; }
	Equipo getCurrentPlayer() { return jugadorActual; }
	GameStateMachine* getGSM() { return gameStateMachine; }
	UniversalShader* getAbilityShader() { return abililyShader; }
	UniversalShader* getMovementShader() { return movementShader; }
	UniversalShader* getAttackShader() { return attackShader; }

	void aumentarAcciones() { accionesPorTurno--; };
	int getAcciones() const { return accionesPorTurno; }	
	int& getMana1()  { return mana_1; } //Para interfaz
	int& getMana2()  { return mana_2; }

	int getTurnosActuales()  { return turnosActuales; }

	bool restaMana(int m, int& mana);
	bool manaSuficiente(int m, int mana) const;

	int getPorcentaje();
	int getPorcentajeSurrender();

	int getPintado1() { return pintado_1; };
	int getPintado2() { return pintado_2; };

	void aumentaPintado1(int n) { pintado_1 += n ; };
	void aumentaPintado2(int n) { pintado_2 += n ; };
};
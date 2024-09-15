#pragma once
#include <vector>
#include "Assets/game/Values.h"
#include "Assets/game/PlayState.h"

#include <iostream>
using namespace std;

class GameStateMachine;

/*
* CharactersSelected gestiona los personajes seleccionados en el menú de selección de personaje.
*/

class CharactersSelected
{
private:
    // Máximo de personajes en la baraja.
    const int max = 6;
    // Número total de personajes presentados.
    const int numP = 13;

    // Vector que mantiene la selección de los personajes del jugador 1.
    vector<bool> chars;
    // Vector que mantiene la selección de los personajes del jugador 2.
    vector<bool> chars2;

    // Contador de personajes
    int cont = 0;
    int equipo_ = 0;

public:
    // Constructora.
    CharactersSelected();
    // Destructora.
    ~CharactersSelected() { }
    // Método que selecciona/deselecciona un personaje.
    void updatePersonaje(Unit pj);
    // Método que pasa a la partida cuando se han seleccionado max personajes.
    void play(GameStateMachine* gsm);
    void clientPlay(GameStateMachine* gsm, int mapa, int tileset);

    void setEquipo(int equipo) { equipo_ = equipo; }
    void updateCont() { cont = 0; }
    int getCont() { return cont; }
    int getEquipo() { return equipo_; }
    int getMax() { return max; }

private:
    void selectPersonaje(vector<bool>& ch, Unit pj);
};
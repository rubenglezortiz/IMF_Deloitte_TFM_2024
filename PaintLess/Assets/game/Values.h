#pragma once


enum Unit { Alquimista, Arquitecta, Bomba, Cazador, Druida, Esqueleto, Golem, Kirin, Lobo, Monaguillo, Picara, Tanque, Vikingo };
enum UnitAnim { IdleA, DeathA, A_A_A };



struct AnimInfo {
	int finCol;
};

struct SpriteSheetInfo {
	int animInfo[4];
	int rows, cols;
};


typedef unsigned int uint;

namespace UnitInfo {
	enum TipoCarta { Ataque, Defensa, Utilidad };

	const uint numUnidades = 13;

	const uint Movimiento[2] = { 4, 2 };
	const uint mana[numUnidades] =	   { 3, 3, 3, 2, 3, 1, 4, 2, 3, 3, 3, 4, 3 };
	const uint cooldown[numUnidades] = { 3, 3, 3, 2, 3, 1, 3, 3, 2, 2, 3, 2, 3 };

										//Nº sprites por fila , nº filas nª columnas
	const SpriteSheetInfo spriteSheetInfo[numUnidades] = {{{4,5,6}, 3, 6},   //Alquimista
														  {{4,5,6}, 3, 6},   //Arquitecta
														  {{4,6,0}, 2, 6},   //Bomba
														  {{4,6,6}, 3, 6},   //Cazador
														  {{5,6,6}, 3, 6},   //Druida
														  {{4,5,4}, 3, 5},   //Esqueleto
														  {{7,8,7}, 3, 8},   //Golem
														  {{4,6,4}, 3, 6},   //Kirin
														  {{5,8,6}, 3, 8},   //Lobo
														  {{4,6,8}, 3, 8},   //Monaguillo
														  {{7,8,6}, 3, 8},   //Picara
														  {{4,4,4}, 3, 4},   //Tanque
														  {{4,5,6}, 3, 6}    //Vikingo
	};



	//const uint numUnidades = 13;
	//const uint Ataque = {1};
	//
	//const uint Cooldown = {3};
	//const uint Mana = {3};
	//const uint Vida = {2};
	//const TipoCarta tipoCarta = {TipoCarta::Ataque};

	/*
	const uint health[numUnidades] = { 2, 2, 3, 1, 2, 1, 4, 2, 2, 1, 2, 4, 1 };

	const uint damage[numUnidades] = { 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 0, 1 };
	//const TipoCarta tiposCartas[numUnidades] = { Utilidad, Utilidad, Utilidad, Ataque, Utilidad, Ataque, Defensa, Ataque, Utilidad, Defensa, Ataque, Defensa, Ataque };
	}*/

	/*Ataque[Arquitecta] =1;
	Ataque[Bomba] = 0;
	Ataque[Cazador] = 1;
	Ataque[Druida] = 1;
	Ataque[Esqueleto] = 1;
	Ataque[Golem] = 1;
	Ataque[Kirin] = 1;
	Ataque[Lobo] = 0;
	Ataque[Monaguillo] = ;
	Ataque[Picara] = ;
	Ataque[Tanque] = ;
	Ataque[Vikingo] = ;*/
}
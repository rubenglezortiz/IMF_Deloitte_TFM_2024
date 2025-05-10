// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere

class Ability_Creeper;
class Ability;
class Attack;
class ButtonCharacterSelection;
class ButtonDescription;
class ButtonHovered;
class ButtonSelected;
class ButtonSettings;
class ButtonSurrender;
class ButtonPlay;
class ButtonTick;
class ButtonVolume;
class DeckSpawn;
class FramedImage;
class GameMap;
class Health;
class Image;
class Interfaz;
class MenuButton;
class Movimiento;
class PointOnImage;
class Transform;
class Transform2;
class DieAfterXTurns;
class UniversalShader;
class ComponentBuffer;

#define _CMPS_LIST_  \
	Ability						    ,  \
	Ability_Creeper				    ,  \
	Attack							,  \
	ButtonCharacterSelection		,  \
	ButtonDescription               ,  \
	ButtonHovered					,  \
	ButtonSelected					,  \
	ButtonSettings					,  \
	ButtonSurrender					,  \
	ButtonPlay						,  \
	ButtonTick						,  \
	ButtonVolume					,  \
	DeckSpawn					    ,  \
	FramedImage					    ,  \
	GameMap							,  \
	Health						    ,  \
	Image							,  \
	Interfaz						,  \
	MenuButton				   	    ,  \
	Movimiento						,  \
	PointOnImage					,  \
	Transform						,  \
	Transform2						,  \
    DieAfterXTurns					,  \
	UniversalShader					,  \
	ComponentBuffer

	// groups

struct Personajes;
struct Attack;
struct Defense;
struct Utility;
struct Mazo1;
struct Mazo2;
struct Muro;
struct Equipo_Rojo;
struct Equipo_Azul;

#define _GRPS_LIST_ \
	Personajes	, \
	Attack , \
	Defense , \
	Utility , \
	Mazo1       , \
	Mazo2       , \
	Muro,    \
	Equipo_Rojo , \
	Equipo_Azul 


// handlers
struct Hdlr_1;
struct Mapa;
struct BoardManager;

#define _HDLRS_LIST_ Hdlr_1, Mapa, BoardManager
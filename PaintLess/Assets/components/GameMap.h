#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows-

#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Transform2.h"
#include "Image.h"
#include "../ecs/Component.h"
#include "../game/OffsetInfo.h"

#include <string>
#include <fstream>
#include <array>
#include <vector>
//#include "../../checkML.h"

//#include "Game.h"
class Game;
using namespace std;

typedef unsigned int uint;

enum Color { Azul, Verde, Rojo, Amarillo, Ninguno };
enum TipoCasilla { Pintable, NoPintable, Base };

class PlayState;

struct Casilla
{
	Color color;
	TipoCasilla tipoCasilla;
	Entity* character;
	Entity* obstaculo;
	bool enredadera;
};

class GameMap : public Component {
private:
	Casilla** cells;
	int rows, cols;
	int cellWidth, cellHeight;
	int tileSet, level;
	int nCasPintables;
	PlayState* playState;
	vector<Entity*> casillas;

public:
	GameMap(int level, int tileSet, PlayState* playState);
	virtual ~GameMap();
	virtual void init();
	void loadMap();
	bool setColor(const Vector2D& cas, Color color);
	void setEstado(const Vector2D& cas, TipoCasilla tipo);
	void setCharacter(const Vector2D& cas, Entity* e);
	void setObstaculo(const Vector2D& cas, Entity* e);
	void setCreeper(const Vector2D& cas, bool e);
	void removeCharacter(const Vector2D& cas);
	void removeObstaculo(const Vector2D& cas);
	bool casillaValida(const Vector2D& cas);
	bool movimientoPosible(const Vector2D& cas);
	bool movimientoPosibleEnredadera(const Vector2D& cas);
	bool ataquePosible(const Vector2D& cas);
	Color getColor(Vector2D cas);
	void render();
	int getRows() const { return rows; };
	int getColumns() const { return cols; }
	int getCellWidth() const { return cellWidth; };
	int getCellHeight() const { return cellHeight; };
	int getNumCasPintables() const { return nCasPintables; };
	Entity* getCharacter(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].character; }
	Entity* getObstaculo(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].obstaculo; }
	bool getCreeper(const Vector2D& pos) { return cells[(int)pos.getY()][(int)pos.getX()].enredadera; }
	bool esPintable(const Vector2D& pos);
	TipoCasilla getTipoCasilla(Vector2D pos) { return cells[(int)pos.getY()][(int)pos.getX()].tipoCasilla; }
	PlayState* getPlayState() { return playState; }
	int binarySearchCell(Vector2D pos);
	Vector2D MapCoordsToSDLPoint(Vector2D coords) const { //Pasar de coordenadas del mapa a pixeles
		Vector2D p{ (coords.getX() * cellWidth) + OFFSET_X, (coords.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP };
		return p;
	}
	
	Vector2D SDLPointToMapCoords(Vector2D p) { //Pasar de pixeles a coordenadas del mapa
		//como las casillas neceitan int se hace aqui el casteo
		int X = (p.getX() - OFFSET_X) / cellWidth;
		int Y = (p.getY() - OFFSET_Y - OFFSET_TOP) / cellHeight;
		//como vector2D es float se hace el casteo pero el valor va a ser .0000
		Vector2D coords{ std::min(std::max((float)X, 0.0f), (float)cols - 1), std::min(std::max((float)Y, 0.0f), (float)rows - 1) };
		return coords;
	}
};
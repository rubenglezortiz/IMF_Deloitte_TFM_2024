#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "./Transform.h"
class UniversalShader;

class GameStateMachine;

class Movimiento : public Component {
public:
	Movimiento(PlayState* playState, uint casillasAMover = 1) : tr_(nullptr), mapa(nullptr), selected(false), cellWidth(0), cellHeight(0), playState(playState), casillasAMover(casillasAMover) {}
	virtual ~Movimiento() {};


	void init() override;
	void update() override;
	void finTurno() override;
	void focus() { focused = true; };
	void clearMovShader();

	void setStun(int x) { stun = x * 2; }
	int getStun() const { return stun; }
	void MoveCharacter(const Vector2D& posIni, const Vector2D& posMovimiento);
	//Vector2D MapCoordsToSDLPoint(Vector2D coords) const { //Pasar de coordenadas del mapa a pixeles
	//	Vector2D p{ (coords.getX() * cellWidth) , (coords.getY() * cellHeight)/* + DESPL*/ };
	//	return p;
	//}

	//Vector2D SDLPointToMapCoords(Vector2D p) const { //Pasar de pixeles a coordenadas del mapa
	//	//como las casillas neceitan int se hace aqui el casteo
	//	int X = p.getX() / cellWidth;
	//	int Y = p.getY()/*-DESPL*/ / cellHeight;
	//	//como vector2D es float se hace el casteo pero el valor va a ser .0000
	//	Vector2D coords{ (float)X,(float)Y };
	//	return coords;
	//}

private:
	UniversalShader* movementShader;
	Transform* tr_;
	GameMap* mapa;
	bool selected;
	int cellWidth;
	int cellHeight;
	PlayState* playState = nullptr;
	GameStateMachine* gsm;
	void colorea(Vector2D posIni, Vector2D posFin, Color color);
	uint casillasAMover;
	std::vector<Vector2D> casillasPintarShader;

	int stun = false;
	bool focused;
};
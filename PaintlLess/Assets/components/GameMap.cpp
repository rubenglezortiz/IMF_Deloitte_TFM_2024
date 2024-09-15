#include "GameMap.h"
#include "Ability.h"
#include <iostream>
#include <fstream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "../game/Game.h"
#include "./PointOnImage.h"
#include "../game/PlayState.h"
#include "../game/OffsetInfo.h"

using namespace std;

GameMap::GameMap(int level, int tileSet, PlayState* playState) : playState(playState), level(level), tileSet(tileSet) {}

GameMap::~GameMap() {
	for (int r = 0; r < rows; ++r)
		delete cells[r];
	delete[] cells;
}

void GameMap::init() {
	loadMap();
}
void GameMap::loadMap() {
	tmx::Map map;
	if (!map.load(sdlutils().tiled().at("mapa" + to_string(level)))) return;
		const auto & layers = map.getLayers();
	for (const auto& layer : layers) {
		if (layer->getType() == tmx::Layer::Type::Tile) {
			const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();

			cols = tileLayer.getSize().x; rows = tileLayer.getSize().y;
			cells = new Casilla * [rows];
			for (int r = 0; r < rows; ++r) {
					cells[r] = new Casilla[cols];
			}

			int alto = sdlutils().height() - OFFSET_Y * 2;
			int ancho = sdlutils().width() - OFFSET_X * 2;
			cellWidth = ancho / cols;
			cellHeight = (alto / rows);
			nCasPintables = 0;

			auto tiles = tileLayer.getTiles();
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					auto* casilla = entity_->getMngr()->addEntity(RenderLayer::Fondo);

					casilla->addComponent<Transform2>(Vector2D(j * cellWidth + OFFSET_X, (i * cellHeight) + OFFSET_Y + OFFSET_TOP), cellWidth, cellHeight);
					string tileset = "tileset" + to_string(tileSet);
					int casTiled = tiles[i * cols + j].ID - 1;
					casilla->addComponent<Image>(&sdlutils().images().at(tileset), 4, 3, casTiled / 3, casTiled % 3);
					if (tileSet < 3) {
						if (casTiled < 8) {
							// Agua
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
						}
						else if (casTiled < 10) {
							// Base
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Base;
						}
						else {
							// Roca
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Pintable;
							nCasPintables++;
							auto* casilla = entity_->getMngr()->addEntity();
							Vector2D pos = MapCoordsToSDLPoint(Vector2D(j, i));
							casilla->addComponent<Transform>(pos, cellWidth, cellHeight);
							casillas.push_back(casilla);
						}
					}
					else {
						if (casTiled == 11) {
							// Agua
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::NoPintable;
						}
						else if (casTiled == 9) {
							// Base
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Base;
						}
						else {
							// Roca
							cells[i][j].color = Color::Ninguno;
							cells[i][j].tipoCasilla = TipoCasilla::Pintable;
							nCasPintables++;
							auto* casilla = entity_->getMngr()->addEntity();
							Vector2D pos = MapCoordsToSDLPoint(Vector2D(j, i));
							casilla->addComponent<Transform>(pos, cellWidth, cellHeight);
							casillas.push_back(casilla);
						}
					}
					cells[i][j].character = nullptr;
					cells[i][j].obstaculo = nullptr;
					cells[i][j].enredadera = false;
				}
			}
		}
	}

}

void GameMap::render() {
	/*SDL_Rect desRect;

	desRect.h = sdlutils().height();
	desRect.w = sdlutils().width();
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			desRect.x = c * desRect.w;
			desRect.y = r * desRect.h;
		}
	}*/
}

bool GameMap::setColor(const Vector2D& cas, Color color) {
	
	int i = binarySearchCell(cas);
	bool colorChanged = false;
	Casilla casillaActual = cells[(int)cas.getY()][(int)cas.getX()];
	if (casillaActual.tipoCasilla == Pintable) {
		if (getColor(cas) != color && getColor(cas) != Ninguno && color == Azul) {
			casillas[i]->getComponent<Image>()->setTexture(&sdlutils().images().at("rojo"));
			playState->aumentaPintado1(1);
			playState->aumentaPintado2(-1);
			colorChanged = true;
		}
		else if (getColor(cas) != color && getColor(cas) != Ninguno && color == Rojo) {
			casillas[i]->getComponent<Image>()->setTexture(&sdlutils().images().at("azul"));
			playState->aumentaPintado2(1);
			playState->aumentaPintado1(-1);
			colorChanged = true;
		}
		else if (getColor(cas) != Ninguno && color == Ninguno) {
			casillas[i]->removeComponent<Image>();
			if (getColor(cas) == Azul)playState->aumentaPintado1(-1);
			else playState->aumentaPintado2(-1);
		}
		else if (getColor(cas) == Ninguno) {
			if (color == Azul) {
				casillas[i]->addComponent<Image>(&sdlutils().images().at("rojo"));
				playState->aumentaPintado1(1);
			}
			else {
				casillas[i]->addComponent<Image>(&sdlutils().images().at("azul"));
				playState->aumentaPintado2(1);
			}
		}

		cells[(int)cas.getY()][(int)cas.getX()].color = color;
		return colorChanged;
	}
}

int GameMap::binarySearchCell(Vector2D cas) {
	Vector2D cas2 = MapCoordsToSDLPoint(cas);
	int i = 0;
	bool busqueda = false;

	while (i < casillas.size() && !busqueda) {
		if (casillas[i]->getComponent<Transform>()->getPos() == cas2)
			busqueda = true;
		else i++;
	}
	return i;
}

void GameMap::setEstado(const Vector2D& cas, TipoCasilla tipo) {
	assert(casillaValida(cas)); //si a este m�todo se le pasa una casilla de fuera del mapa, error de ejecuci�n
	cells[(int)cas.getY()][(int)cas.getX()].tipoCasilla = tipo;
}

void GameMap::setCharacter(const Vector2D& cas, Entity* e) {
	cells[(int)cas.getY()][(int)cas.getX()].character = e;
}

void GameMap::setObstaculo(const Vector2D& cas, Entity* e) {
	cells[(int)cas.getY()][(int)cas.getX()].obstaculo = e;
}

void GameMap::setCreeper(const Vector2D& cas, bool e) {
	cells[(int)cas.getY()][(int)cas.getX()].enredadera = e;
}

void GameMap::removeCharacter(const Vector2D& cas) {
	cells[(int)cas.getY()][(int)cas.getX()].character = nullptr;
}

void GameMap::removeObstaculo(const Vector2D& cas) {
	cells[(int)cas.getY()][(int)cas.getX()].obstaculo = nullptr;
}

// Salta excepci�n al no encontrar 4 casillas en el borde inferior.


Color GameMap::getColor(Vector2D cas) {
	return cells[(int)cas.getY()][(int)cas.getX()].color;
}

bool GameMap::casillaValida(const Vector2D& cas) //SUPONEMOS QUE EST� BIEN, ACEPTAMOS CAMBIOS XDD
{
	return cas.getX() >= 0 && cas.getX() < getColumns() && cas.getY() >= 0 && cas.getY() < getRows();
}


bool GameMap::movimientoPosible(const Vector2D& cas) {
	if (!casillaValida(cas))return false;
	int x = cas.getX(); int y = cas.getY();
	return (cells[y][x].tipoCasilla != NoPintable && cells[y][x].character == nullptr && cells[y][x].obstaculo == nullptr);
}

bool GameMap::movimientoPosibleEnredadera(const Vector2D& cas) {
	if (!casillaValida(cas))return false;
	int x = cas.getX(); int y = cas.getY();
	if (cells[y][x].character != nullptr && cells[y][x].obstaculo == nullptr)
		return ((cells[y][x].character->hasComponent<Movimiento>() || cells[y][x].character->hasComponent<Attack>()) && cells[y][x].tipoCasilla != NoPintable);
	else if (cells[y][x].obstaculo == nullptr)
		return cells[y][x].tipoCasilla != NoPintable;
	else return false;
}

// Solo ataca a los personajes y obstáculos que no estén en base.
bool GameMap::ataquePosible(const Vector2D& cas) {
	if (!casillaValida(cas)) return false;
	int x = cas.getX(); int y = cas.getY();
	if (cells[y][x].obstaculo != nullptr && getTipoCasilla(cas) != Base) {
		return true;
	}

	// Ha de hacer distinci�n entre personaje amigo y enemigo.
	if (cells[y][x].character != nullptr && getTipoCasilla(cas) != Base) {
		if (playState->getTurno() == Primero)
			return !cells[y][x].character->hasGroup<Equipo_Azul>();
		else
			return !cells[y][x].character->hasGroup<Equipo_Rojo>();
	}
	else return false;
}

bool GameMap::esPintable(const Vector2D& pos) {
	if (!casillaValida(pos)) return false;
	auto character = getCharacter(pos);
	if (character != nullptr && character->hasComponent<Transform>())
		return (getTipoCasilla(SDLPointToMapCoords(getCharacter(pos)->getComponent<Transform>()->getPos())) == Pintable);
	else throw "En esta casilla no hay ningún personaje con Transform";
}


//GameMap GameMap::CreaMapa(string filename) {
//	MapCell s = MapCell.Empty;
//	ifstream in(filename);
//	int fil, col, temp;
//	in >> fil >> col;
//	GameMap m(fil,col);
//	for (int i = 0; i < fil; i++) {
//		for (int j = 0; i < col; i++) {
//			in >> temp;
//			if (temp == 0 || (temp >= 4 && temp <= 9))
//				//m[i, j] = MapCell.Empty;
//			else if(temp == 1)
//				//m[i, j] = MapCell.Wall;
//			else if (temp == 2)
//				//m[i, j] = MapCell.Food;
//			else if (temp == 3)
//				//m[i, j] = MapCell.Vitamins
//			else
//				//throw exception string("Tipo de casilla invalido");
//		}
//	}	
//	in.close();
//}
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "ecs.h"
#include "Entity.h"

enum class RenderLayer { Fondo, Tablero, Tablero2, Tablero3, Personajes, Interfaz};

class Manager {
public:

	Manager();
	virtual ~Manager();

	// entities
	Entity* addEntity(RenderLayer layer = RenderLayer::Tablero) {
		Entity *e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			entities_.emplace_back(e);
			renderLayers[(int)layer].emplace_back(e);
		}
		return e;
	}

	// handlers
	template<typename T>
	inline void setHandler(Entity *e) {
		hdlrs_[ecs::hdlrIdx<T>] = e;
	}

	template<typename T>
	inline Entity* getHandler() {
		return hdlrs_[ecs::hdlrIdx<T>];
	}

	inline const std::vector<Entity*>& getEnteties() {
		return entities_;
	}

	void update();
	void render();
	void refresh();
	void finTurno();

private:

	std::vector<Entity*> entities_;
	std::vector<std::vector<Entity*>> renderLayers;
	std::array<Entity*, ecs::maxHdlr> hdlrs_;
};


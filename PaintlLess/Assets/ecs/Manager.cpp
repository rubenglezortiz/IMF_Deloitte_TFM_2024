// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

#include <algorithm>

Manager::Manager() {
	for (int i = 0; i < 6; i++)
	{
		renderLayers.push_back(std::vector<Entity*>());
	}
}

Manager::~Manager() {
	for (auto e : entities_) {
		delete e;
	}
}

void Manager::refresh() {
	// remove dead entities from the list of entities
	int size = entities_.size();
	entities_.erase( //
		std::remove_if( //
			entities_.begin(), //
			entities_.end(), //
			[](const Entity* e) { //
				if (e->isActive()) {
					return false;
				}
				else {
					delete e;
					e = nullptr;
					return true;
				}
			}), //
		entities_.end());

	if (size == entities_.size()) return;
	for (int i = 0; i < renderLayers.size(); i++)
		renderLayers[i].erase(std::remove_if( //
			renderLayers[i].begin(), //
			renderLayers[i].end(), //
			[](const Entity* e) { //
				return !e->isActive();
			}), //
			renderLayers[i].end());
}

//void Manager::refresh() {
//
//	auto toRemove = std::remove_if( //
//			entities_.begin(), //
//			entities_.end(), //
//			[](const Entity *e) { //
//				return !e->isActive();
//			});
//
//	std::for_each(toRemove, entities_.end(), [](const Entity *e) {
//		delete e;
//	});
//
//	// remove dead entities from the list of entities
//	entities_.erase(toRemove, entities_.end());
//}

void Manager::update() {
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->update();
}

void Manager::render() {
	//auto n = entities_.size();
	//for (auto i = 0u; i < n; i++)
	//	entities_[i]->render();

	for (std::vector<Entity*> entities : renderLayers)
	{
		for (Entity* entity : entities)
		{
			entity->render();
		}
	}
}


void Manager::finTurno() {
	auto n = entities_.size();
	for (auto i = 0u; i < n; i++)
		entities_[i]->finTurno();
}
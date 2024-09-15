#include "EntityFactory.h"
#include "Ability_Alchemist.h"
#include "Ability_Architect.h"
#include "Ability_Bomb.h"
#include "Ability_Druid.h"
#include "Ability_Golem.h"
#include "Ability_Kirin.h"
#include "Ability_Priest.h"
#include "Ability_Rogue.h"
#include "Ability_Skeleton.h"
#include "Ability_Tank.h"
#include "Ability_Viking.h"
#include "Ability_Wolf.h"
#include "Attack.h"
#include "FramedImage.h"
#include "GameMap.h"
#include "Health.h"
#include "Transform2.h"
#include "Image.h"
#include "Movimiento.h"
#include "../game/Values.h"
#include "../game/PlayState.h"
#include "../game/GameStateMachine.h"

void EntityFactory::health(Entity* c, int l) {
	c->addComponent<Health>(l);
}

void EntityFactory::movement(PlayState* playState, Entity* c, Uint8 casillasAMover) {
	c->addComponent<Movimiento>(playState, casillasAMover);
}

void EntityFactory::image(Entity* c, string t) {
	c->addComponent<Image>(&sdlutils().images().at(t));
}

void EntityFactory::animation(Entity* c, string tex, int d, Unit p) {
	if (c->hasGroup<Equipo_Azul>())
		c->addComponent<FramedImage>(&sdlutils().images().at(tex + "R"), d, p);
	else
		c->addComponent<FramedImage>(&sdlutils().images().at(tex + "A"), d, p);
}

void EntityFactory::attack(PlayState* playState, Entity* c, int dmg, int dmgCri, int probCritico, int range, string s) {
	c->addComponent<Attack>(playState, dmg, dmgCri, probCritico, range, s);
}

void EntityFactory::createCharacter(Manager* manager, GameMap* mapa, PlayState* playState, int character, int equipo, Vector2D pos) {
	Entity* ctr = manager->addEntity(RenderLayer::Personajes);

	ctr->addComponent<Transform>(pos, Vector2D(), 50.0f, 50.0f, 0.0f);
	ctr->setGroup<Personajes>(ctr);
	if (equipo == Primero) ctr->setGroup<Equipo_Rojo>(ctr);
	else ctr->setGroup<Equipo_Azul>(ctr);

	switch (character) {
	case Alquimista:
		animation(ctr, "alquimistaSheet", 150, Alquimista);	 movement(playState, ctr, 2); health(ctr, 2);
		ctr->addComponent<Ability>(new Ability_Alchemist());
		break;
	case Arquitecta:
		animation(ctr, "arquitectaSheet", 150, Arquitecta);	 movement(playState, ctr); health(ctr, 2);
		ctr->addComponent<Ability>(new Ability_Architect());
		break;
	case Bomba:
		animation(ctr, "bombaSheet", 150, Bomba);   movement(playState, ctr, 1); health(ctr, 2);
		ctr->addComponent<Ability>(new Ability_Bomb());
		break;
	case Cazador:
		animation(ctr, "cazadorSheet", 180, Cazador); movement(playState, ctr);
		health(ctr, 1); attack(playState, ctr, 1, 0, 0, 2, "arqueroSound");
		break;
	case Druida:
		animation(ctr, "druidaSheet", 125, Druida);   movement(playState, ctr); health(ctr, 2);
		ctr->addComponent<Ability>(new Ability_Druid());
		break;
	case Esqueleto:
		animation(ctr, "esqueletoSheet", 150, Esqueleto);  movement(playState, ctr); health(ctr, 1); attack(playState, ctr);
		ctr->addComponent<Ability>(new Ability_Skeleton());
		break;
	case Golem:
		animation(ctr, "golemSheet", 120, Golem);	health(ctr, 4); attack(playState, ctr); ctr->addComponent<Movimiento>(playState, 0);
		ctr->addComponent<Ability>(new Ability_Golem());
		break;
	case Kirin:
		animation(ctr, "kirinSheet", 150, Kirin);	movement(playState, ctr); health(ctr, 2); attack(playState, ctr);
		ctr->addComponent<Ability>(new Ability_Kirin());
		break;
	case Lobo:
		animation(ctr, "loboSheet", 150, Lobo);	  movement(playState, ctr); health(ctr, 2);
		ctr->addComponent<Ability>(new Ability_Wolf());
		break;
	case Monaguillo:
		animation(ctr, "monaguilloSheet", 150, Monaguillo); movement(playState, ctr); health(ctr, 1); attack(playState, ctr);
		ctr->addComponent<Ability>(new Ability_Priest());
		break;
	case Picara:
		animation(ctr, "picaraSheet", 150, Picara);	  movement(playState, ctr); health(ctr, 2); attack(playState, ctr, 2, 4, 50);
		break;
	case Tanque:
		animation(ctr, "tanqueSheet", 150, Tanque);    movement(playState, ctr); health(ctr, 3); attack(playState, ctr);
		ctr->addComponent<Ability>(new Ability_Tank());
		break;
	case Vikingo:
		animation(ctr, "vikingoSheet", 150, Vikingo);  movement(playState, ctr); health(ctr, 1);
		ctr->addComponent<Ability>(new Ability_Viking());
		break;
	}
	mapa->setCharacter(mapa->SDLPointToMapCoords(ctr->getComponent<Transform>()->getPos()), ctr);
}

bool EntityFactory::spawneableCell(Vector2D p, vector<Vector2D> casillasSpawn) {
	int i = 0;
	bool encontrado = false;
	while (i < casillasSpawn.size() && !encontrado) {
		if (casillasSpawn[i] == p) encontrado = true;
		else i++;
	}
	return encontrado;
}
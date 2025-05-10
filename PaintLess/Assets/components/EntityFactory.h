#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../game/PlayState.h"
#include "../game/values.h"

class PlayState;
class EntityFactory : public Component {
public:
	EntityFactory() {}
	virtual ~EntityFactory() {}

	static void health(Entity* character, int lives);
	static void attack(PlayState* playState, Entity* character, int damage = 1, int dmgCri = 0, int probCritico = 0, int range = 1, string s = "ataqueSound");
	static void movement(PlayState* playState, Entity* character, Uint8 casillasAMover = 1);
	static void image(Entity* character, string tex);
	static void animation(Entity* character, string tex, int d, Unit p);

	static void createCharacter(Manager* manager, GameMap* mapa, PlayState* playState, int character, int equipo, Vector2D posClick);
	static bool spawneableCell(Vector2D pos, vector<Vector2D> casillasSpawn);
};
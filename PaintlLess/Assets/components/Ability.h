#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "./Transform.h"
#include<vector>
#include "../sdlutils/InputHandler.h"
#include "Movimiento.h"
#include "../game/AbilityStruct.h"
#include "UniversalShader.h"

using AbilityFunction = void(int x, int y, GameMap* map, Manager* manager);


class Ability : public Component {
public:
	Ability() : characterTr(nullptr), tex(nullptr), map(nullptr), selected(false), cellWidth(0), cellHeight(0), form(form), type(type), shaderDistance(1){}
	Ability(AbilityStruct* data);

	virtual ~Ability() { delete abilityData; }

	virtual void init();
	virtual void update() ;
	virtual void finTurno();
	virtual void OnDie();
	virtual void OnCross();

	virtual bool TryExecuteAbility(int x, int y);
	void Shade();
	void AbilityShader(ShaderForm sf, ShaderType st=nullSh, int d = 1);
	void freeAbilityShader();
	virtual bool abilityCheck(const Vector2D& pos); //comprueba si en el segundo clic se está clicando 
		
	GameMap* getMap() { return map; }
	std::vector<Vector2D> getCells() { return abilityCells; }										//en una casilla donde se puede colocar la habilidad
	bool ability_usable = true;

protected:
	AbilityStruct* abilityData;
	ShaderForm form;
	ShaderType type;
	std::vector<Vector2D> abilityCells;
	Transform* characterTr; //¿lo necesitan todas las habilidades?
	Texture* tex;
	GameMap* map;
	UniversalShader* abilityShader;
	selectorColor sel;
	bool selected;
	int cellWidth, cellHeight;
	int shaderDistance;
	PlayState* playState = nullptr;
	void SetShaderDistance(int distance) { shaderDistance = distance; };
};
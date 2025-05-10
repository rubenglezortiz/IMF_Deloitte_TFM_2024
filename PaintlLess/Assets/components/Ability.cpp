#include "./Ability.h"
#include "../game/PlayState.h"
#include "../game/GameStateMachine.h"
#include "../game//AbilityStruct.h"

Ability::Ability(AbilityStruct* data) : characterTr(nullptr), tex(nullptr), map(nullptr), abilityData(data),
sel(abilityData->selector), selected(false), cellWidth(0), cellHeight(0),
form(abilityData->shaderForm), type(abilityData->shaderType), shaderDistance(data->distance) { }

void Ability::init() {
	abilityData->initiliceData(this);
	map = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	assert(map != nullptr);
	characterTr = entity_->getComponent<Transform>();
	assert(characterTr != nullptr);
	cellWidth = map->getCellWidth();
	cellHeight = map->getCellHeight();
	string s;
	switch (sel)
	{
	case selector:
		s = "selectorAb";
		break;
	case selectorA:
		s = "selectorA";
		break;
	case selectorH:
		s = "selectorH";
		break;
	default:
		s = "selectorAb";
		break;
	}
	tex = &sdlutils().images().at(s);
	auto mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	playState = mapa->getPlayState();
	abilityShader = playState->getAbilityShader();
}

bool Ability::TryExecuteAbility(int x, int y)
{
	return abilityData->AbilityExecute(x, y);
	freeAbilityShader();
}

void Ability::Shade()
{
	AbilityShader(form, type, shaderDistance);
	abilityShader->setCells(&abilityCells);
	abilityShader->resetAnim();
	abilityShader->setTexture(tex);
}

void Ability::AbilityShader(ShaderForm sf, ShaderType st, int d) {

	UniversalShader::AbilityShader(sf, st, d, entity_, map, &abilityCells);
}

void Ability::freeAbilityShader() { abilityCells.clear(); abilityShader->setCells(nullptr); }

bool Ability::abilityCheck(const Vector2D& pos) {
	bool check = false;
	int cont = 0;
	while (!check && cont < abilityCells.size()) {
		if (pos == abilityCells[cont])check = true;
		cont++;
	}
	return check;
}

void Ability::update() {
	if (map->getPlayState()->getTurno() == Primero && entity_->hasGroup<Equipo_Rojo>())
		return;
	if (map->getPlayState()->getTurno() == Segundo && entity_->hasGroup<Equipo_Azul>())
		return;

	auto pos = entity_->getComponent<Transform>()->getPos();

	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (ih().getMouseButtonState(ih().RIGHT)) {
		if (!selected && entity_->hasComponent<Movimiento>() && playState->getAcciones() > 0 && entity_->getComponent<Movimiento>()->getStun() == 0) {
			if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && ability_usable && map->esPintable(map->SDLPointToMapCoords(pos))) {
				selected = true;
				Shade();
			}
		}
		else {
			selected = false;
			freeAbilityShader();
		}
	}
	if (ih().getMouseButtonState(ih().LEFT)) {
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = map->SDLPointToMapCoords(Vector2D(mX, mY));

			if (abilityCheck(posMovimiento)) {
				pos.setX(posMovimiento.getX() * cellWidth);
				pos.setY(posMovimiento.getY() * cellHeight);
				int x = posMovimiento.getX();
				int y = posMovimiento.getY();
				auto character = this->map->getCharacter(Vector2D(x, y));
				if (character != nullptr) {
					auto mov = character->getComponent<Movimiento>();
					if (mov != nullptr) mov->focus();
				}
				Vector2D charPos = characterTr->getPos();

				if (playState->getGSM()->isOnline())
					playState->getGSM()->getNetworkManager()->sendExecuteAbility(charPos.getX(), charPos.getY(),
						std::forward<int>(x), std::forward<int>(y));

				if (TryExecuteAbility(x, y)) {
					playState->aumentarAcciones();
					ability_usable = false;
				}
			}
			selected = false;
			freeAbilityShader();
		}
	}
}


void Ability::finTurno()
{
	ability_usable = true;
	freeAbilityShader();
	abilityData->finTurno();
}

void Ability::OnDie()
{
	abilityData->OnDie();
	freeAbilityShader();
	Vector2D pos = characterTr->getPos();
}

void Ability::OnCross()
{
	abilityData->OnCross();
}

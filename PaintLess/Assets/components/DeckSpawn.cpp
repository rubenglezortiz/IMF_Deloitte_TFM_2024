#include "DeckSpawn.h"
#include "Ability_Alchemist.h"
#include "Ability_Architect.h"
#include "Ability_Bomb.h"
#include "Ability_Druid.h"
#include "Ability_Golem.h"
#include "Ability_Kirin.h"
#include "Ability_Priest.h"
#include "Ability_Rogue.h"
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
#include "../components/EntityFactory.h"

void DeckSpawn::init() {
	tr_ = entity_->getComponent<Transform2>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	tex = &sdlutils().images().at("selectorSp");
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	playState = mapa->getPlayState();
	turno = playState->getTurno();
}

void DeckSpawn::spawnShader(int e) {
	int k = 0;
	int l = 2;
	if (e == Primero) {
		k = mapa->getColumns() - 2;
		l = mapa->getColumns();
	}
	if (personaje == 6) {
		if (e == Primero) k -= 2;
		else l += 2;
	}
	for (int i = k; i < l; ++i) {
		for (int j = 0; j < mapa->getColumns(); ++j) {
			Vector2D cas = Vector2D(i, j);
			if (mapa->casillaValida(cas))
				if (mapa->getTipoCasilla(cas) == Base || (turno == Primero && mapa->getColor(cas) == Azul) || (turno == Segundo && mapa->getColor(cas) == Rojo))
					if (mapa->getCharacter(cas) == nullptr && mapa->getObstaculo(cas) == nullptr)
						casillasSpawn.push_back(cas);
		}
	}
}

void DeckSpawn::render() {
	SDL_Rect dest;
	for (Vector2D casilla : casillasSpawn) {
		dest.x = casilla.getX() * cellWidth + OFFSET_X;
		dest.y = casilla.getY() * cellHeight + OFFSET_Y + OFFSET_TOP;
		dest.h = cellHeight;
		dest.w = cellWidth;
		tex->render(dest);
	}
	dest.x = tr_->getPos().getX();
	dest.y = tr_->getPos().getY();
	dest.h = tr_->getH();
	dest.w = tr_->getW();

	if (playState->getCurrentPlayer() == 1 && cool1 > 0)
		sdlutils().images().at("cold" + to_string(cool1)).render(dest);
	else if (playState->getCurrentPlayer() == 0 && cool0 > 0)
		sdlutils().images().at("cold" + to_string(cool0)).render(dest);
	else {
		if (hover || selected) {
			dest.x = tr_->getPos().getX();
			dest.y = tr_->getPos().getY();
			dest.h = tr_->getH();
			dest.w = tr_->getW();
			sdlutils().images().at("marcoCarta").render(dest);
		}
	}	
}

void DeckSpawn::update() {
	auto pos = entity_->getComponent<Transform2>()->getPos();
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	
	hover = (mX > pos.getX() && mX < pos.getX() + tr_->getW() && mY > pos.getY() && mY < pos.getY() + tr_->getH()) ? true : false;
		
	if (ih().getMouseButtonState(ih().LEFT)) {		
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			if (EntityFactory::spawneableCell(posMovimiento, casillasSpawn) && playState->getCurrentPlayer() == 1 && playState->restaMana(UnitInfo::mana[personaje], playState->getMana1())) {
				EntityFactory::createCharacter(entity_->getMngr(), mapa, playState,personaje, 0, posMovimiento);
				cool1 += UnitInfo::cooldown[personaje];
				if (playState->getGSM()->isOnline()) playState->getGSM()->getNetworkManager()->sendSpawnCharacter(personaje, posMovimiento.getX(), posMovimiento.getY());
			}
			else if (EntityFactory::spawneableCell(posMovimiento, casillasSpawn) && playState->getCurrentPlayer() == 0 && playState->restaMana(UnitInfo::mana[personaje], playState->getMana2())) {
				EntityFactory::createCharacter(entity_->getMngr(), mapa, playState, personaje, 1, posMovimiento);
				cool0 += UnitInfo::cooldown[personaje];
				if (playState->getGSM()->isOnline()) playState->getGSM()->getNetworkManager()->sendSpawnCharacter(personaje, posMovimiento.getX(), posMovimiento.getY());
			}
			selected = false;
			freeShader();
		}
		else if (mX > pos.getX() && mX < pos.getX() + tr_->getW() && mY > pos.getY() && mY < pos.getY() + tr_->getH()) {
			
			if (isSpawnable()) {
				selected = true;			
				spawnShader(playState->getCurrentPlayer());
				sdlutils().soundEffects().at("seleccionSound").play();
			}
		}
	}
	if (ih().getMouseButtonState(ih().RIGHT)) {
		selected = false;
		freeShader();
	}
	if (turno != playState->getTurno()) {
		selected = false;
		freeShader();
		turno = playState->getTurno();
	}
}

void DeckSpawn::freeShader() {
	casillasSpawn.clear();
}

void DeckSpawn::finTurno() {
	if (cool0 > 0 && playState->getCurrentPlayer() == 0) cool0--;
	if (cool1 > 0 && playState->getCurrentPlayer() == 1) cool1--;
}

bool DeckSpawn::isSpawnable() const {
	return
		playState->getCurrentPlayer() == 1 &&
		playState->manaSuficiente(UnitInfo::mana[personaje], playState->getMana1()) && cool1 == 0
		||
		playState->getCurrentPlayer() == 0 &&
		playState->manaSuficiente(UnitInfo::mana[personaje], playState->getMana2()) && cool0 == 0;
}
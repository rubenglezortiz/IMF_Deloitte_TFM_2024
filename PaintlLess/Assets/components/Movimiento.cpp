#include "./Movimiento.h"
#include "../game/PlayState.h"
#include "../game/OffsetInfo.h"
#include "../game/GameStateMachine.h"
#include "Ability.h"

void Movimiento::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	gsm = playState->getGSM();
	assert(tr_ != nullptr);
	movementShader = playState->getMovementShader();
	movementShader->setDelayCellsRender(false);
}

void Movimiento::update() {
	if (casillasAMover == 0) return;
	if ((gsm->isOnline() &&
		((gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) ||
			(!gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero))) ||

		(!gsm->isOnline() && (entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero || entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) && stun == 0)) {
		if (playState->getAcciones() == 0)
		{
			clearMovShader();
			return;
		}
		auto& pos = tr_->getPos();
		Vector2D posIni = pos;
		//poner el puntero de entidad de la casilla del mapa a NULL

		if (ih().getMouseButtonState(ih().LEFT)) {
			int mX = ih().getMousePos().first;
			int mY = ih().getMousePos().second;
			if (selected) {
				//esto se debe hacer en movementshader
				Vector2D posMovimiento = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
				bool shouldMove = false;
				for (Vector2D casilla : casillasPintarShader)
				{
					shouldMove |= posMovimiento == casilla;
					if (shouldMove) break;
				}

				if (shouldMove)
				{
					MoveCharacter(posIni, posMovimiento);
					if(gsm->isOnline())gsm->getNetworkManager()->sendMoveMessage(posIni.getX(), posIni.getY(), posMovimiento.getX(), posMovimiento.getY());
				}
				selected = false;
				clearMovShader();
			}
			else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight) {
				selected = true;
				//movShader->casillasPosiblesRecu(mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasChecked, casillasAMover);
				UniversalShader::checkCasillasPosiblesMov(mapa->SDLPointToMapCoords(Vector2D(pos.getX(), pos.getY())), casillasAMover, mapa, &casillasPintarShader, stun);
				movementShader->setCells(&casillasPintarShader);
				movementShader->resetAnim();
				//sdlutils().soundEffects().at("click").setChunkVolume(5);
				sdlutils().soundEffects().at("click").play(); //-----------------------------------------------------------					
			}
		}
		if (ih().getMouseButtonState(ih().RIGHT) || focused) {
			selected = false;
			focused = false;
			clearMovShader();
		}
	}
}

void Movimiento::finTurno()
{
	clearMovShader();
	selected = false;
	if (stun > 0)
	{
		stun--;
	}
}

void Movimiento::clearMovShader()
{
	casillasPintarShader.clear();
	movementShader->setCells(nullptr);
}

void Movimiento::MoveCharacter(const Vector2D& posIni, const Vector2D& destino)
{
	auto& pos = tr_->getPos();
	sdlutils().soundEffects().at("moveSound").play();
	mapa->removeCharacter(mapa->SDLPointToMapCoords(pos));
	pos.setX((destino.getX() * cellWidth) + OFFSET_X);
	pos.setY((destino.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
	mapa->setCharacter(mapa->SDLPointToMapCoords(pos), entity_);
	playState->aumentarAcciones();

	if (entity_->hasGroup<Equipo_Azul>()) colorea(posIni, pos, Azul);
	else colorea(posIni, pos, Rojo);
}

void Movimiento::colorea(Vector2D posIni, Vector2D posFin, Color color)
{
	float  desplX, desplY;
	//solo se pueden mover en linea recta en un eje, no hay diagonal, por lo que el que de != 0 de estos es el eje en el que
	//Se mueve
	Vector2D posCoor = mapa->SDLPointToMapCoords(Vector2D(posFin.getX(), posFin.getY()));
	Vector2D posIniCoor = mapa->SDLPointToMapCoords(Vector2D(posIni.getX(), posIni.getY()));

	desplX = posCoor.getX() - posIniCoor.getX();
	desplY = posCoor.getY() - posIniCoor.getY();
	bool haCambiado = false;;
	if (desplX != 0) {
		if (desplX > 0) {  //mirar el alquimista si pinta de mas
			for (int a = posIniCoor.getX(); a <= posCoor.getX(); a++) {
				haCambiado = mapa->setColor((Vector2D(a, posCoor.getY())), color);
			}
		}
		else {
			for (int a = posIniCoor.getX(); a >= posCoor.getX(); a--) {
				haCambiado = mapa->setColor((Vector2D(a, posCoor.getY())), color);
			}
		}
	}


	if (desplY != 0) {
		if (desplY > 0) {
			for (int a = posIniCoor.getY(); a <= posCoor.getY(); a++) {
				haCambiado = mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
		else {
			for (int a = posIniCoor.getY(); a >= posCoor.getY(); a--) {
				haCambiado = mapa->setColor((Vector2D(posCoor.getX(), a)), color);
			}
		}
	}

	if (haCambiado) {
		Ability* ab = entity_->getComponent<Ability>();
		if (ab != nullptr) ab->OnCross();
	}

}

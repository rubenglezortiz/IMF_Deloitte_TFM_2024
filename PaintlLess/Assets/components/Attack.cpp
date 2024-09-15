#include "Attack.h"
#include "../game/PlayState.h"
#include "../game/GameStateMachine.h"

void Attack::init() {
	tr_ = entity_->getComponent<Transform>();
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();
	cellWidth = mapa->getCellWidth();
	cellHeight = mapa->getCellHeight();
	gsm = playState->getGSM();
	attackShader_ = playState->getAttackShader();
}

void Attack::update() {
	if ((gsm->isOnline() &&
		((gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo) ||
			(!gsm->getNetworkManager()->isMaster() && entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero))) ||

		(!gsm->isOnline() && (entity_->hasGroup<Equipo_Azul>() && playState->getTurno() == Primero || entity_->hasGroup<Equipo_Rojo>() && playState->getTurno() == Segundo))) {
			{
				if (entity_->getComponent<Movimiento>()->getStun() == 0) attack();
			}
	}
}

void Attack::finTurno()
{
	casillasAtaque.clear();
	attackShader_->setCells(nullptr);
	selected = false;
	ability_usable = true;
}

void Attack::attack() {
	auto& pos = tr_->getPos();

	if (ih().getMouseButtonState(ih().LEFT)) {
		int mX = ih().getMousePos().first;
		int mY = ih().getMousePos().second;
		if (selected) {
			//esto se debe hacer en movementshader
			Vector2D cas = mapa->SDLPointToMapCoords(Vector2D(mX, mY));
			// Se tendría que hacer diferenciación entre el equipo del personaje.
			if (canAttack(cas)) {
				bool ataqueCrit = (rand() % 100 + 1) < probCrit;
				int currentDmg = ataqueCrit ? dmgCrit : dmg;
				attackDelegate(cas, currentDmg);
				auto gsm = playState->getGSM();
				if (gsm->isOnline())
				{
					Vector2D posInMap = mapa->SDLPointToMapCoords(pos);
					gsm->getNetworkManager()->sendAttack(posInMap.getX(), posInMap.getY(), cas.getX(), cas.getY(), std::forward<int>(currentDmg));
				}
				//sdlutils().soundEffects().at(sound).setChunkVolume(15);
				ability_usable = false;
				playState->aumentarAcciones(); //en realidad se restan acciones 
				attackSound();
			}
			selected = false;
			casillasAtaque.clear();
			attackShader_->setCells(nullptr);
		}
		else if (mX > pos.getX() && mX < pos.getX() + cellWidth && mY > pos.getY() && mY < pos.getY() + cellHeight && playState->getAcciones() > 0 && ability_usable) {
			selected = true;
			attackShader();
		}
	}
	if (ih().getMouseButtonState(ih().RIGHT)) {
		selected = false;
		casillasAtaque.clear();
		attackShader_->setCells(nullptr);
	}
}

void Attack::attackDelegate(const Vector2D& cas, const int& damage)
{
	auto* mCha = mapa->getCharacter(cas);
	if (mCha != nullptr)
	{
		Health* vida = mapa->getCharacter(cas)->getComponent<Health>();
		if (vida != nullptr) vida->hit(damage);
	}
	auto* mObs = mapa->getObstaculo(cas);
	if (mObs != nullptr)
		mapa->getObstaculo(cas)->getComponent<Health>()->hit(damage);
}

void Attack::attackSound()
{
	entity_->getComponent<FramedImage>()->setAnim(A_A_A);
	sdlutils().soundEffects().at(sound).play(); //-----
}

void Attack::attackShader() {

	UniversalShader::attackShader(tr_->getPos(), mapa, &casillasAtaque, range);
	attackShader_->resetLerp();
	attackShader_->resetCasillasRendered();
	attackShader_->setCells(&casillasAtaque);
}

bool Attack::canAttack(Vector2D cas) {
	bool esPosible = false;
	int i = 0;
	while (!esPosible && i < casillasAtaque.size()) {
		if (cas == casillasAtaque[i])esPosible = true;
		i++;
	}
	return esPosible;
}
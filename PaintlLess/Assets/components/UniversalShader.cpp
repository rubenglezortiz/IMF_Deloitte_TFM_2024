#include "UniversalShader.h"
#include "../game/AbilityStruct.h"
#include "../game/PlayState.h"
#include "../../checkML.h"

void UniversalShader::update()
{
	if (lerpTime < 1) lerpTime += 0.25;
}

void UniversalShader::render()
{
	if (arrayPointer == nullptr || tex == nullptr || arrayPointer->empty()) return;
	SDL_Rect dest;
	int cellWidth = mapa->getCellWidth();
	int cellHeight = mapa->getCellHeight();
	if (arrayPointer->size() > 0) {
		int aux = casillasRendered;
		for (Vector2D casilla : *arrayPointer) {
			float lerp = 0;
			if (aux > 0 && delayedCellsRender) lerp = 1;
			else if (aux == 0 || !delayedCellsRender) lerp = lerpTime;

			dest.w = cellWidth * lerp;
			dest.h = cellHeight * lerp;
			dest.x = (casilla.getX() * cellWidth + OFFSET_X) + cellWidth / 2 - dest.w / 2;
			dest.y = ((casilla.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP) + cellHeight / 2 - dest.h / 2;

			tex->render(dest);
			if (aux <= 0 && lerpTime >= 1)
			{
				if (!delayedCellsRender) continue;
				lerpTime = 0;
				casillasRendered++;
				break;
			}
			else aux--;
		}
	}
}

void UniversalShader::setCells(std::vector<Vector2D>* arrayPointer)
{
	this->arrayPointer = arrayPointer;
}

void UniversalShader::setTexture(Texture* tex)
{
	this->tex = tex;
}

void UniversalShader::resetLerp()
{
	lerpTime = 0;
}

void UniversalShader::resetCasillasRendered()
{
	casillasRendered = 0;
}

void UniversalShader::resetAnim()
{
	resetLerp();
	resetCasillasRendered();
}

void UniversalShader::checkCasillasPosiblesMov(const Vector2D& cSelected, uint casillasAMover, GameMap* mapa, std::vector<Vector2D>* casillasAPintar, const int& stun)
{
	if (stun > 0) return;
	Vector2D casillaAMirar;
	//Si se encuentra un obstaculo, el booleano correspondiente se pone a false
	//y no se comprueba mas por ese camino
	bool iz, der, up, down = iz = der = up = true;
	for (int i = 1; i <= casillasAMover; i++)
	{
		casillaAMirar = Vector2D(cSelected.getX() + i, cSelected.getY());
		if (mapa->movimientoPosible(casillaAMirar) && der)
			casillasAPintar->push_back(casillaAMirar);
		else der = false;

		casillaAMirar = Vector2D(cSelected.getX() - i, cSelected.getY());
		if (mapa->movimientoPosible(casillaAMirar) && iz)
			casillasAPintar->push_back(casillaAMirar);
		else iz = false;

		casillaAMirar = Vector2D(cSelected.getX(), cSelected.getY() + i);
		if (mapa->movimientoPosible(casillaAMirar) && up)
			casillasAPintar->push_back(casillaAMirar);
		else up = false;

		casillaAMirar = Vector2D(cSelected.getX(), cSelected.getY() - i);
		if (mapa->movimientoPosible(casillaAMirar) && down)
			casillasAPintar->push_back(casillaAMirar);
		else down = false;
	}
}

void UniversalShader::attackShader(const Vector2D& pos, GameMap* mapa, std::vector<Vector2D>* casillasAtaque, int range)
{
	Vector2D mapPos = mapa->SDLPointToMapCoords(pos);

	int i = 1; bool canAt = true;

	while (i <= range && canAt) {
		Vector2D posUp = Vector2D(0, i) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posUp)) {
			if (mapa->ataquePosible(posUp))
				casillasAtaque->push_back(posUp);
			else if (mapa->getObstaculo(posUp) != nullptr)
			{
				casillasAtaque->push_back(posUp);
				canAt = false;
			}
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posRight = Vector2D(i, 0) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posRight)) {
			if (mapa->ataquePosible(posRight))
				casillasAtaque->push_back(posRight);
			else if (mapa->getObstaculo(posRight) != nullptr)
			{
				casillasAtaque->push_back(posRight);
				canAt = false;
			}
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posLeft = Vector2D(-i, 0) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posLeft)) {
			if (mapa->ataquePosible(posLeft))
				casillasAtaque->push_back(posLeft);
			else if (mapa->getObstaculo(posLeft) != nullptr)
			{
				casillasAtaque->push_back(posLeft);
				canAt = false;
			}
		}
		i++;
	}
	i = 1; canAt = true;

	while (i <= range && canAt) {
		Vector2D posDown = Vector2D(0, -i) + mapPos;
		if (mapa->getTipoCasilla(mapPos) == TipoCasilla::Base)
		{
			i++;
			continue;
		}
		if (mapa->casillaValida(posDown)) {
			if (mapa->ataquePosible(posDown))
				casillasAtaque->push_back(posDown);
			else if (mapa->getObstaculo(posDown) != nullptr)
			{
				casillasAtaque->push_back(posDown);
				canAt = false;
			}
		}
		i++;
	}
}

void UniversalShader::AbilityShader(ShaderForm sf, ShaderType st, int d, Entity* entity_, GameMap* map, std::vector<Vector2D>* abilityCells)
{
	Vector2D posCh = entity_->getComponent<Transform>()->getPos();
	posCh = entity_->getComponent<Transform>()->getPos();
	posCh = map->SDLPointToMapCoords(posCh);
	if (sf == Cross) {
		Vector2D posUp = Vector2D(0, d) + posCh;
		Vector2D posRight = Vector2D(d, 0) + posCh;
		Vector2D posLeft = Vector2D(-d, 0) + posCh;
		Vector2D posDown = Vector2D(0, -d) + posCh;

		if (st == AttackSh) {
			if (map->ataquePosible(posUp)) abilityCells->push_back(posUp);
			if (map->ataquePosible(posRight)) abilityCells->push_back(posRight);
			if (map->ataquePosible(posLeft)) abilityCells->push_back(posLeft);
			if (map->ataquePosible(posDown)) abilityCells->push_back(posDown);
		}
		else if (st == KirinSh) {
			if (map->movimientoPosible(posUp) && (map->getCharacter(posUp + Vector2D(0, -1)) != nullptr ||
				map->getCreeper(posUp + Vector2D(0, -1))))abilityCells->push_back(posUp);


			if (map->movimientoPosible(posRight) && (map->getCharacter(posRight + Vector2D(-1, 0)) != nullptr ||
				map->getCreeper(posRight + Vector2D(-1, 0)))) abilityCells->push_back(posRight);


			if (map->movimientoPosible(posLeft) && (map->getCharacter(posLeft + Vector2D(1, 0)) != nullptr ||
				map->getCreeper(posLeft + Vector2D(1, 0)))) abilityCells->push_back(posLeft);
			if (map->movimientoPosible(posDown) && (map->getCharacter(posDown + Vector2D(0, 1)) != nullptr ||
				map->getCreeper(posDown + Vector2D(0, 1)))) abilityCells->push_back(posDown);
		}
		else if (st == DruidaSh) {
			if (map->movimientoPosibleEnredadera(posUp)) abilityCells->push_back(posUp);
			if (map->movimientoPosibleEnredadera(posRight)) abilityCells->push_back(posRight);
			if (map->movimientoPosibleEnredadera(posLeft)) abilityCells->push_back(posLeft);
			if (map->movimientoPosibleEnredadera(posDown)) abilityCells->push_back(posDown);
		}
		else {
			if (map->movimientoPosible(posUp)) abilityCells->push_back(posUp);
			if (map->movimientoPosible(posRight)) abilityCells->push_back(posRight);
			if (map->movimientoPosible(posLeft)) abilityCells->push_back(posLeft);
			if (map->movimientoPosible(posDown)) abilityCells->push_back(posDown);
		}
	}
	else if (sf == TxT) {
		Vector2D posUp = Vector2D(0, -1) + posCh;
		if (map->casillaValida(posUp) && map->getTipoCasilla(posUp) == Pintable) abilityCells->push_back(posUp);
		Vector2D posUpLeft = Vector2D(-1, -1) + posCh;
		if (map->casillaValida(posUpLeft) && map->getTipoCasilla(posUpLeft) == Pintable) abilityCells->push_back(posUpLeft);
		Vector2D posUpRight = Vector2D(1, -1) + posCh;
		if (map->casillaValida(posUpRight) && map->getTipoCasilla(posUpRight) == Pintable) abilityCells->push_back(posUpRight);
		Vector2D posRight = Vector2D(1, 0) + posCh;
		if (map->casillaValida(posRight) && map->getTipoCasilla(posRight) == Pintable) abilityCells->push_back(posRight);
		Vector2D posLeft = Vector2D(-1, 0) + posCh;
		if (map->casillaValida(posLeft) && map->getTipoCasilla(posLeft) == Pintable) abilityCells->push_back(posLeft);
		Vector2D posDown = Vector2D(0, 1) + posCh;
		if (map->casillaValida(posDown) && map->getTipoCasilla(posDown) == Pintable) abilityCells->push_back(posDown);
		Vector2D posDownLeft = Vector2D(-1, 1) + posCh;
		if (map->casillaValida(posDownLeft) && map->getTipoCasilla(posDownLeft) == Pintable) abilityCells->push_back(posDownLeft);
		Vector2D posDownRight = Vector2D(1, 1) + posCh;
		if (map->casillaValida(posDownRight) && map->getTipoCasilla(posDownRight) == Pintable) abilityCells->push_back(posDownRight);
	}
	else if (sf == ShaderWolf) {
		std::vector<Vector2D> casillas;
		Vector2D detras;
		if (entity_->hasGroup<Equipo_Rojo>()) {
			casillas = { {1, 0}, {2, 0}, { 1, 1}, {2, 1}, {1, -1}, {2, -1} }; //Izquierda ==> Derecha
			detras = Vector2D(1, 0);
		}
		else {
			casillas = { {-1, 0}, {-2, 0}, {-1, 1}, {-2, 1}, {-1, -1}, {-2, -1} }; //Derecha ==> Izquierda
			detras = Vector2D(-1, 0);
		}

		Vector2D posWolf = map->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos());

		for (int i = 0; i < casillas.size(); i++) { // 12, 2 por cada lao
			if (map->casillaValida(casillas[i] + posWolf)) {
				//Hay personaje en el 1
				Entity* character = map->getCharacter(casillas[i] + posWolf);
				if (character != nullptr) {
					if (map->esPintable(map->SDLPointToMapCoords(character->getComponent<Transform>()->getPos())))
						if (map->casillaValida(casillas[i] + posWolf + detras))
							abilityCells->push_back(casillas[i] + posWolf);
				}
				//Hay personaje en el 2
				else {
					character = map->getCharacter(casillas[i + 1] + posWolf);
					if (character != nullptr)
						if (map->esPintable(map->SDLPointToMapCoords(character->getComponent<Transform>()->getPos())))
							if (map->casillaValida(character->getComponent<Transform>()->getPos() + detras * 2))
								abilityCells->push_back(casillas[i + 1] + posWolf);

				}
			}
			i++;
		}
	}
	else {
		bool findObj = false;

		Vector2D atDir;
		if (map->getPlayState()->getTurno() == Primero) atDir = Vector2D(-1, 0);
		else atDir = Vector2D(1, 0);

		posCh = map->SDLPointToMapCoords(entity_->getComponent<Transform>()->getPos()) + atDir;

		while (!findObj && map->casillaValida(posCh)) {
			if (map->ataquePosible(posCh))
				findObj = true;
			if (map->getCharacter(posCh) != nullptr) {
				if (map->ataquePosible(posCh))
					abilityCells->push_back(posCh);
			}
			else
				abilityCells->push_back(posCh);
			posCh = posCh + atDir;
		}
		if (!findObj) abilityCells->clear();
	}
}

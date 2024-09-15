#include "PointOnImage.h"

void PointOnImage::init() {
	mapa = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>();

	dest.h = mapa->getCellHeight();
	dest.w = mapa->getCellWidth();
}

void PointOnImage::update() {
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;

	//Ver si la posición actual del cursor es igual a la anterior
	//La posicion se guarda en coordenadas de mapa porque que coordenadas SDL no podemos
	//ver cuando cambia de casilla
	if (!(mapa->SDLPointToMapCoords({ (float)mX, (float)mY }) == currentPosition))
	{
		lastPosition = currentPosition; //Si no lo es, la ultima posicion es la actual anterior
		currentPosition = mapa->SDLPointToMapCoords({ (float)mX, (float)mY }); //Actualizamos la actual
		lerpTime = 0; //Activamos el lerp
	}

	if (lerpTime < 1) lerpTime += 0.1; //Aumentar el lerp

		//Convertir posiciones de mapa a SDL
	Vector2D lastPosSDL = mapa->MapCoordsToSDLPoint(lastPosition);
	Vector2D currentPosSDL = mapa->MapCoordsToSDLPoint(currentPosition);

	dest.x = LerpFuncts::Lerp(lastPosSDL.getX(), currentPosSDL.getX(), lerpTime);
	dest.y = LerpFuncts::Lerp(lastPosSDL.getY(), currentPosSDL.getY(), lerpTime);
}
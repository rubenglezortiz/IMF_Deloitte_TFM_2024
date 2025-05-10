#include "Transform.h"
#include "../game/OffsetInfo.h"
void Transform::init() {

	mapa = entity_->getMngr()->getHandler<Mapa>(); //COMENTADO POR FALLO DE RUTAS Y PK NO SABEMOS Q ES EL MAP
	
	if (mapa == nullptr) return;


	int cellWidth = mapa->getComponent<GameMap>()->getCellWidth();
	int cellHeight = mapa->getComponent<GameMap>()->getCellHeight();

	width_ = cellWidth;
	height_ = cellHeight;

	pos_.setX((pos_.getX() * cellWidth) + OFFSET_X);
	pos_.setY((pos_.getY() * cellHeight) + OFFSET_Y + OFFSET_TOP);
}
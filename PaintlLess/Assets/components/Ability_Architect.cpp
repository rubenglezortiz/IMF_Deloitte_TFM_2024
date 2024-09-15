#include "Ability_Architect.h"
#include "../game/OffsetInfo.h"

Ability_Architect::Ability_Architect() : AbilityStruct(selectorColor::selector, ShaderForm::Cross, ShaderType::DefenseSh){}

bool Ability_Architect::AbilityExecute(int x, int y)
{
	Ability* self = this->getAbility();
	Entity* e = self->getEntity()->getMngr()->addEntity(RenderLayer::Tablero3);
	e->setGroup<Muro>(true);

	e->addComponent<Transform>(
		Vector2D(x, y), //Posicion
		Vector2D(),     //Velocidad
		50.0f,          //Ancho
		50.0f,          //Alto
		0.0f);

	e->addComponent<Image>(&sdlutils().images().at("wall"));
	e->addComponent<Health>(2);
	self->getEntity()->getComponent<FramedImage>()->setAnim(A_A_A);
	self->getMap()->setObstaculo(Vector2D(x, y), e);
	self->getMap()->setColor(Vector2D(x, y), Ninguno);
	return true;
}

#include "Ability_Golem.h"

Ability_Golem::Ability_Golem(){}

void Ability_Golem::OnDie()
{
    GameMap* map = this->getAbility()->getMap();
    Entity* entity_ = this->getAbility()->getEntity();
    Transform* characterTr = entity_->getComponent<Transform>();

    Vector2D pos = map->SDLPointToMapCoords(characterTr->getPos());
    auto* e = entity_->getMngr()->addEntity(RenderLayer::Tablero3);
    e->addComponent<Transform>(
        pos, //Posicion
        Vector2D(),     //Velocidad
        50.0f,          //Ancho
        50.0f,          //Alto
        0.0f);
    e->addComponent<Image>(&sdlutils().images().at("wall"));
    e->addComponent<Health>(2);
    map->setCharacter(pos, e);
}

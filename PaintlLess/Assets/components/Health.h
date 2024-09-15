#pragma once

#include "../ecs/Component.h"
#include "./Image.h"
#include "../ecs/Entity.h"
#include "./Ability_Bomb.h"
#include "./Ability_Golem.h"
#include "./FramedImage.h"


class Health : public Component { //lleva este componente la destrucci�n del objeto??
public:
    Health(int l) : lives(l), livesMax(l+1), tr(nullptr), mapa(nullptr), tex(nullptr) {}
    virtual ~Health() {}

    void init() override;
    void render() override;
    void hit(int damage);
    void healMonaguillo(int healing);
    void heal(int healing = 1);
    static void kill(GameMap* mapa, Entity* entity_);
    //void setLives();
    int getLives() { return lives; };

private:
    GameMap* mapa;
    Transform* tr;
    Texture* tex;
    int lives;
    int livesMax;
};
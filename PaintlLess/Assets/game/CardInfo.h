#pragma once

#include "../ecs/Component.h"

class Texture;

enum TipoCarta {Ataque, Defensa, Utilidad};

enum TipoMov { Normal, Saltar };

using uint = unsigned int;
struct InfoMov {
	uint alcanceMov, energiaMov;
	TipoMov tipoMov;
	InfoMov(uint alc, TipoMov tipoMov) : alcanceMov(alc), tipoMov(tipoMov), energiaMov(1) {}
	InfoMov() :alcanceMov(0), tipoMov(Normal), energiaMov(1) {}
};


class CardInfo : public Component {

public:

	CardInfo(TipoCarta tipoCarta, Texture* ic, uint	currentCD, uint maxCD, uint vida, uint mana, uint alcanceAt, uint damage, uint alcMov, TipoMov tipoMov);

	void setCurrentCoolDown(int currentCD);
	int getCurrentCooDown() const;
	int getmaxCoolDown() const;
	int getMana() const;
	int getVida() const;
	int getAlcanceAt() const;
	int getDamage() const;

	InfoMov getInfoMov() const;
	TipoCarta getTipoCarta() const;
private:

	uint currentCoolDown, maxCoolDown, mana, vida, alcanceAt, damage;
	Texture* icono;
	TipoCarta tipoCarta;
	InfoMov infoMov;
};
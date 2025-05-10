#include "CardInfo.h"

CardInfo::CardInfo(TipoCarta tipoC, Texture* ic, uint currentCD, uint maxCD, uint vida, uint m, uint alcanceAtaque, uint d, uint alcMov, TipoMov tipoMov) {
	tipoCarta = tipoC;
	icono = ic;
	currentCoolDown = currentCD;
	maxCoolDown = maxCD;
	mana = m;
	alcanceAt = alcanceAtaque;
	damage = d;
	infoMov = InfoMov(alcMov, tipoMov);

	if (tipoCarta == TipoCarta::Defensa) {
		infoMov.energiaMov = 2;
	}
}

void CardInfo::setCurrentCoolDown(int currentCD) {
	currentCoolDown = currentCD;
}

int CardInfo::getCurrentCooDown() const { return currentCoolDown; };
int CardInfo::getmaxCoolDown() const { return maxCoolDown; };
int CardInfo::getMana() const { return  mana; };
int CardInfo::getVida() const { return vida; };
int CardInfo::getAlcanceAt() const { return  alcanceAt; };
int CardInfo::getDamage() const { return  damage; };

InfoMov CardInfo::getInfoMov() const { return infoMov; };
TipoCarta CardInfo::getTipoCarta() const { return tipoCarta; }
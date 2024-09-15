#include "Interfaz.h"
#include "../game/PlayState.h"
#include "../game/GameStateMachine.h"
#include "../game/SettingsState.h"
#include "ButtonSettings.h"

void Interfaz::init() {
	playState = entity_->getMngr()->getHandler<Mapa>()->getComponent<GameMap>()->getPlayState();
	texEnergy = &sdlutils().images().at("energia");
	texTurno = &sdlutils().images().at("turno");
	numCasillasPintables = entity_->getComponent<GameMap>()->getNumCasPintables();
	gsm_ = playState->getGSM();
	auto* opciones = entity_->getMngr()->addEntity(RenderLayer::Interfaz);
	opciones->addComponent<Transform2>(Vector2D(sdlutils().width() - 275 + 65, 10), 78, 78);
	opciones->addComponent<Image>(&sdlutils().images().at("opciones"));
	opciones->addComponent<ButtonSettings>(gsm_, menuOpciones);
}

void Interfaz::render() {
	int mana;
	if (playState->getCurrentPlayer() == 0) mana = playState->getMana2();
	else mana  = playState->getMana1();
	destNum.x  = 200;
	destMana.x = 80;
	if (mana == 10)
		destNum.w = 100;
	else 
		destNum.w = 70;
	destMana.w = 225;
	destNum.h  = 90; destMana.h = 100;
	destNum.y  = sdlutils().height() - 110;
	destMana.y = sdlutils().height() - 120;
	sdlutils().images().at("mana").render(destMana);
	Texture(sdlutils().renderer(), to_string(mana), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x7ce5fbff)).render(destNum);	

	destAcciones.x = sdlutils().width()-550 + 40;	//BARRA DE ACCION
	destAcciones.y = 25;
	destAcciones.w = 265;
	destAcciones.h = 45;
	sdlutils().images().at("barraAccion").render(destAcciones);

	destEnergy.x = sdlutils().width() - 520 + 42;	//ENERGIA
	destEnergy.y = 33;
	destEnergy.w = 30;
	destEnergy.h = 29;	

	for (int i = 0; i < playState->getAcciones(); ++i){
		texEnergy->render(destEnergy);
		destEnergy.x = destEnergy.x + destEnergy.w + 15;
	}	

	int turnos = playState->getTurnosActuales();
	destNumTurnos.x = (sdlutils().width() / 2) - 240;
	destNumTurnos.y = 35;
	if (turnos < 10) destNumTurnos.w = 25;
	else {
		destNumTurnos.x -= 25;
		destNumTurnos.w = 50;
	}
	destNumTurnos.h = 30;
	Texture(sdlutils().renderer(), to_string(turnos), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xfff0bcff)).render(destNumTurnos);
	
	destNumTurnos.x = (sdlutils().width() / 2) - 210;
	destNumTurnos.w = 80;
	Texture(sdlutils().renderer(), "/20", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xfff0bcff)).render(destNumTurnos);

	
	destBarraTurnos.h = 45;					//BARRA DE TURNOS
	destBarraTurnos.w = 520;
	destBarraTurnos.x = sdlutils().width() / 2 - 125;
	destBarraTurnos.y = 25;
	sdlutils().images().at("barraTurnos").render(destBarraTurnos);

	destAcciones.x -= 15;
	destAcciones.y -= 10;
	destAcciones.w = 45;
	destAcciones.h = 65;
	sdlutils().images().at("energia1").render(destAcciones);

	destTurnos.x = sdlutils().width() / 2 - 113;	//TURNOS
	destTurnos.y = 37;
	destTurnos.w = 20;
	destTurnos.h = 20;

	for (int i = 0; i < playState->getTurnosActuales(); ++i)
	{
		texTurno->render(destTurnos);
		destTurnos.x = destTurnos.x + destTurnos.w + 5;
	}


	destBarraPorcentajes.x = 145 + 30;
	destBarraPorcentajes.y = 25;
	destBarraPorcentajes.w = 435;
	destBarraPorcentajes.h = 45;
	sdlutils().images().at("barraPorcentajes").render(destBarraPorcentajes);

	destPorcentaje.x = 376;
	destPorcentaje.y = 37;
	destPorcentaje.w = 25;
	destPorcentaje.h = 25;
	sdlutils().images().at("porcentaje").render(destPorcentaje);

	destPorcentaje1.x = 560 + 30;				
	destPorcentaje2.x = 165 + 30;
	destPorcentaje1.y = destPorcentaje2.y = 38;
	destPorcentaje1.w = destPorcentaje2.w = 0;
	destPorcentaje1.h = destPorcentaje2.h = 20;
	
	int off = (destBarraPorcentajes.w - 40) / numCasillasPintables;
	destPorcentaje2.w += playState->getPintado2() * off;
	sdlutils().images().at("porcAzul").render(destPorcentaje2);

	destPorcentaje1.x -= playState->getPintado1() * off;
	destPorcentaje1.w += playState->getPintado1() * off;
	sdlutils().images().at("porcRojo").render(destPorcentaje1);


	casRojo = playState->getPintado1() * 100 / numCasillasPintables;
	casAzul = playState->getPintado2() * 100 / numCasillasPintables;

	numPorcA.y = numPorcR.y = 35;
	numPorcA.h = numPorcR.h = 30;
	if (casAzul >= 10) {
		numPorcA.w = 50;
		numPorcA.x = 115;
	}
	else {
		numPorcA.w = 25;
		numPorcA.x = 140;
	}
	if (casRojo >= 10) {
		numPorcR.w = 50;
	}
	else {
		numPorcR.w = 25;
		numPorcR.x = 620;
	}
	Texture(sdlutils().renderer(), to_string(casAzul), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x7ce5fbff)).render(numPorcA);
	Texture(sdlutils().renderer(), to_string(casRojo), sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xff00dcff)).render(numPorcR);

	SDL_Rect marco;
	marco.x = 0;
	marco.y = 0;
	marco.w = 1920;
	marco.h = 1080;
	if (playState->getCurrentPlayer() == Primero)
		sdlutils().images().at("marcoRosa").render(marco);
	else
		sdlutils().images().at("marcoAzul").render(marco);
}

void Interfaz::menuOpciones(GameStateMachine* gsm) {
	gsm->pushState(new SettingsState(gsm, static_cast<PlayState*>(gsm->currentState())));
}
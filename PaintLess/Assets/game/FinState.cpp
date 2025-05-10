#include "FinState.h"
#include "../sdlutils/InputHandler.h"
#include "GameStateMachine.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/MenuButton.h"
#include "../components/ButtonHovered.h"
#include "ControlState.h"

FinState::FinState(GameStateMachine* gsm, int e, int p) : GameState(gsm) {
	porcentaje = p;
	equipo = e;

	auto* bSalir = mngr_->addEntity(RenderLayer::Fondo);
	bSalir->addComponent<Transform>(Vector2D((sdlutils().width() / 2) - w / 2, (sdlutils().height() - 2 * h) - 50), w, h);
	bSalir->addComponent<Image>(&sdlutils().images().at("salir2"));
	bSalir->addComponent<MenuButton>(gsm, exitMenu);
}

void FinState::init() {
	SDL_Rect dest;
	dest.x = sdlutils().width() / 2 - WIDTH / 2;
	dest.y = sdlutils().height() / 2 - HEIGHT / 2;
	dest.w = WIDTH;
	dest.h = HEIGHT;


	if (equipo == 1) {
		sdlutils().images().at("finpartida").render(dest);
		dest.x = sdlutils().width() / 2 + 450;
		dest.y = sdlutils().height() / 2 - 113;
		dest.w = 150;
		dest.h = 50;
		Texture(sdlutils().renderer(), "AZUL", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x639bffff)).render(dest);

		dest.w = 125;
		dest.x = sdlutils().width() / 2 - 250;
		dest.y = sdlutils().height() / 2 + 3;
		Texture(sdlutils().renderer(), to_string(porcentaje) + "%", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0x639bffff)).render(dest);
	}
	else if (equipo == 0) {
		sdlutils().images().at("finpartida").render(dest);
		dest.x = sdlutils().width() / 2 + 450;
		dest.y = sdlutils().height() / 2 - 113;
		dest.w = 150;
		dest.h = 50;
		Texture(sdlutils().renderer(), "ROJO", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xff00dcff)).render(dest);

		dest.w = 125;
		dest.x = sdlutils().width() / 2 - 250;
		dest.y = sdlutils().height() / 2 + 3;
		Texture(sdlutils().renderer(), to_string(porcentaje) + "%", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xff00dcff)).render(dest);
	}
	else {
		sdlutils().images().at("finpartidaempate").render(dest);
		dest.h = 50;
		dest.w = 125;
		dest.x = sdlutils().width() / 2 - 265;
		dest.y = sdlutils().height() / 2 + 13;
		Texture(sdlutils().renderer(), to_string(porcentaje) + "%", sdlutils().fonts().at("NES-CHIMERA24"), build_sdlcolor(0xd144f0ff)).render(dest);
	}

	mngr_->render();
	sdlutils().presentRenderer();
}

void FinState::update() {
	mngr_->update();
}

void FinState::exitMenu(GameStateMachine* gsm) { //Volver al menu
	if(gsm->isOnline())gsm->getNetworkManager()->restartConnection();
	gsm->restartCharacterSelection();
	gsm->popState();
	gsm->popState();
}
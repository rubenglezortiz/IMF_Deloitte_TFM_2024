#include "MainMenuState.h"
#include "PlayState.h"
#include "SettingsState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"
#include "../components/ButtonHovered.h"
#include "../components/ButtonVolume.h"
#include "GameStateMachine.h"

MainMenuState::MainMenuState(GameStateMachine* gsm) : GameState(gsm) { //Poner las imagenes y posiciones correctamente
	//Crear botones
	sdlutils().showCursor();

	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(0, 0), sdlutils().width(), sdlutils().height());
	menuFondo->addComponent<Image>(&sdlutils().images().at("menu"));

	auto* bOnline = mngr_->addEntity(RenderLayer::Fondo);
	bOnline->addComponent<Transform>(Vector2D((sdlutils().width() / 2) - w / 2, sdlutils().height() - 5 * h), w, h);
	bOnline->addComponent<Image>(&sdlutils().images().at("online1"));
	bOnline->addComponent<MenuButton>(gsm, loadGame, "menuInicioSound");
	bOnline->addComponent<ButtonHovered>(&sdlutils().images().at("online2"));

	auto* bLocal = mngr_->addEntity(RenderLayer::Fondo);
	bLocal->addComponent<Transform>(Vector2D((sdlutils().width() / 2) - w / 2, sdlutils().height() - 4 * h), w, h);
	bLocal->addComponent<Image>(&sdlutils().images().at("local1"));
	bLocal->addComponent<MenuButton>(gsm, newGame, "menuInicioSound");
	bLocal->addComponent<ButtonHovered>(&sdlutils().images().at("local2"));

	auto* bOpc = mngr_->addEntity(RenderLayer::Fondo);
	bOpc->addComponent<Transform>(Vector2D((sdlutils().width() / 2) - w / 2 - 45 / 2, sdlutils().height() - 3 * h), w + 45, h);
	bOpc->addComponent<Image>(&sdlutils().images().at("opciones1"));
	bOpc->addComponent<MenuButton>(gsm, menuOpciones, "menuInicioSound");
	bOpc->addComponent<ButtonHovered>(&sdlutils().images().at("opciones2"));

	auto* bSalir = mngr_->addEntity(RenderLayer::Fondo);
	bSalir->addComponent<Transform>(Vector2D((sdlutils().width() / 2) - w / 2, sdlutils().height() - 2 * h), w, h);
	bSalir->addComponent<Image>(&sdlutils().images().at("salir1"));
	bSalir->addComponent<MenuButton>(gsm, exitApp);
	bSalir->addComponent<ButtonHovered>(&sdlutils().images().at("salir2"));

}

void MainMenuState::newGame(GameStateMachine* gsm) { //Nuevo partida

	gsm->pushState(new CharacterSelectionState(gsm));
}

void MainMenuState::loadGame(GameStateMachine* gsm) { //Cargar partida
	
	gsm->initOnline();
	gsm->pushState(new CharacterSelectionState(gsm));
}

void MainMenuState::menuOpciones(GameStateMachine* gsm) {
	gsm->pushState(new SettingsState(gsm));
}

void MainMenuState::exitApp(GameStateMachine* gsm) { //Salir de la aplicacion	
	ih().setQuit();
}

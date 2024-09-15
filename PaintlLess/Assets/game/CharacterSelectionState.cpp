#include "CharacterSelectionState.h"
#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/MenuButton.h"
#include "../components/ButtonSelected.h"
#include "../components/ButtonCharacterSelection.h"
#include "../components/ButtonDescription.h"
#include "../components/ButtonPlay.h"

#include "GameStateMachine.h"

CharacterSelectionState::CharacterSelectionState(GameStateMachine* gsm) : GameState(gsm) {
	sdlutils().showCursor();

	// FONDO --------------------------------------------------------------
	auto* menuFondo = mngr_->addEntity(RenderLayer::Fondo);
	menuFondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());
	menuFondo->addComponent<Image>(&sdlutils().images().at("menuSP"));

	// BOTONES ------------------------------------------------------------
	auto* ataque = mngr_->addEntity(RenderLayer::Fondo);
	ataque->addComponent<Transform>(Vector2D(0, 0), sdlutils().width() / 3, h / 2);
	ataque->addComponent<Image>(&sdlutils().images().at("botonAt"));
	ataque->addComponent<ButtonCharacterSelection>(0, this, &sdlutils().images().at("botonAt2"));

	auto* defensa = mngr_->addEntity(RenderLayer::Fondo);
	defensa->addComponent<Transform>(Vector2D(sdlutils().width() / 3, 0), sdlutils().width() / 3, h / 2);
	defensa->addComponent<Image>(&sdlutils().images().at("botonDef"));
	defensa->addComponent<ButtonCharacterSelection>(1, this, &sdlutils().images().at("botonDef2"));

	auto* utilidad = mngr_->addEntity(RenderLayer::Fondo);
	utilidad->addComponent<Transform>(Vector2D(2 * (sdlutils().width() / 3), 0), sdlutils().width() / 3, h / 2);
	utilidad->addComponent<Image>(&sdlutils().images().at("botonUt"));
	utilidad->addComponent<ButtonCharacterSelection>(2, this, &sdlutils().images().at("botonUt2"));

	// PERSONAJES ---------------------------------------------------------
	auto posX = sdlutils().width() / 2;

	auto* Alquimista = mngr_->addEntity(RenderLayer::Fondo);
	Alquimista->addComponent<Transform>(Vector2D(posX - 5 * w / 2, offsetY), w, h);
	Alquimista->addComponent<Image>(&sdlutils().images().at("alquimistaSP"));
	Alquimista->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("alquimistaSP2"), &sdlutils().images().at("alquimistaM"), updateAlquimista);
	Alquimista->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("alquimistaD"));
	Alquimista->setGroup<Utility>(true);

	auto* Arquitecta = mngr_->addEntity(RenderLayer::Fondo);
	Arquitecta->addComponent<Transform>(Vector2D(posX - 3 * w / 2, offsetY), w, h);
	Arquitecta->addComponent<Image>(&sdlutils().images().at("arquitectaSP"));
	Arquitecta->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("arquitectaSP2"), &sdlutils().images().at("arquitectaM"), updateArquitecta);
	Arquitecta->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("arquitectaD"));
	Arquitecta->setGroup<Utility>(true);

	auto* Bomba = mngr_->addEntity(RenderLayer::Fondo);
	Bomba->addComponent<Transform>(Vector2D(posX - w / 2, offsetY), w, h);
	Bomba->addComponent<Image>(&sdlutils().images().at("bombaSP"));
	Bomba->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("bombaSP2"), &sdlutils().images().at("bombaM"), updateBomba);
	Bomba->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("bombaD"));
	Bomba->setGroup<Utility>(true);

	auto* Cazador = mngr_->addEntity(RenderLayer::Fondo);
	Cazador->addComponent<Transform>(Vector2D(posX + w / 2, offsetY), w, h);
	Cazador->addComponent<Image>(&sdlutils().images().at("cazadorSP"));
	Cazador->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("cazadorSP2"), &sdlutils().images().at("cazadorM"), updateCazador);
	Cazador->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("cazadorD"));
	Cazador->setGroup<Attack>(true);

	auto* Druida = mngr_->addEntity(RenderLayer::Fondo);
	Druida->addComponent<Transform>(Vector2D(posX + 3 * w / 2, offsetY), w, h);
	Druida->addComponent<Image>(&sdlutils().images().at("druidaSP"));
	Druida->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("druidaSP2"), &sdlutils().images().at("druidaM"), updateDruida);
	Druida->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("druidaD"));
	Druida->setGroup<Attack>(true);

	auto* Esqueleto = mngr_->addEntity(RenderLayer::Fondo);
	Esqueleto->addComponent<Transform>(Vector2D(posX - 3 * w / 2, h + offsetY), w, h);
	Esqueleto->addComponent<Image>(&sdlutils().images().at("esqueletoSP"));
	Esqueleto->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("esqueletoSP2"), &sdlutils().images().at("esqueletoM"), updateEsqueleto);
	Esqueleto->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("esqueletoD"));
	Esqueleto->setGroup<Attack>(true);

	auto* Golem = mngr_->addEntity(RenderLayer::Fondo);
	Golem->addComponent<Transform>(Vector2D(posX - w / 2, h + offsetY), w, h);
	Golem->addComponent<Image>(&sdlutils().images().at("golemSP"));
	Golem->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("golemSP2"), &sdlutils().images().at("golemM"), updateGolem);
	Golem->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("golemD"));
	Golem->setGroup<Defense>(true);

	auto* Kirin = mngr_->addEntity(RenderLayer::Fondo);
	Kirin->addComponent<Transform>(Vector2D(posX + w / 2, h + offsetY), w, h);
	Kirin->addComponent<Image>(&sdlutils().images().at("kirinSP"));
	Kirin->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("kirinSP2"), &sdlutils().images().at("kirinM"), updateKirin);
	Kirin->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("kirinD"));
	Kirin->setGroup<Attack>(true);

	auto* Lobo = mngr_->addEntity(RenderLayer::Fondo);
	Lobo->addComponent<Transform>(Vector2D(posX - 5 * w / 2, 2 * h + offsetY), w, h);
	Lobo->addComponent<Image>(&sdlutils().images().at("loboSP"));
	Lobo->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("loboSP2"), &sdlutils().images().at("loboM"), updateLobo);
	Lobo->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("loboD"));
	Lobo->setGroup<Utility>(true);

	auto* Monaguillo = mngr_->addEntity(RenderLayer::Fondo);
	Monaguillo->addComponent<Transform>(Vector2D(posX - 3 * w / 2, 2 * h + offsetY), w, h);
	Monaguillo->addComponent<Image>(&sdlutils().images().at("monaguilloSP"));
	Monaguillo->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("monaguilloSP2"), &sdlutils().images().at("monaguilloM"), updateMonaguillo);
	Monaguillo->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("monaguilloD"));
	Monaguillo->setGroup<Defense>(true);

	auto* Picara = mngr_->addEntity(RenderLayer::Fondo);
	Picara->addComponent<Transform>(Vector2D(posX - w / 2, 2 * h + offsetY), w, h);
	Picara->addComponent<Image>(&sdlutils().images().at("picaraSP"));
	Picara->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("picaraSP2"), &sdlutils().images().at("picaraM"), updatePicara);
	Picara->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("picaraD"));
	Picara->setGroup<Attack>(true);

	auto* Tanque = mngr_->addEntity(RenderLayer::Fondo);
	Tanque->addComponent<Transform>(Vector2D(posX + w / 2, 2 * h + offsetY), w, h);
	Tanque->addComponent<Image>(&sdlutils().images().at("tanqueSP"));
	Tanque->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("tanqueSP2"), &sdlutils().images().at("tanqueM"), updateTanque);
	Tanque->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("tanqueD"));
	Tanque->setGroup<Defense>(true);

	auto* Vikingo = mngr_->addEntity(RenderLayer::Fondo);
	Vikingo->addComponent<Transform>(Vector2D(posX + 3 * w / 2, 2 * h + offsetY), w, h);
	Vikingo->addComponent<Image>(&sdlutils().images().at("vikingoSP"));
	Vikingo->addComponent<ButtonSelected>(gsm, &sdlutils().images().at("vikingoSP2"), &sdlutils().images().at("vikingoM"), updateVikingo);
	Vikingo->addComponent<ButtonDescription>(gsm, &sdlutils().images().at("vikingoD"));
	Vikingo->setGroup<Attack>(true);

	// Botón de paso de partida.
	auto* Boton = mngr_->addEntity(RenderLayer::Fondo);
	Boton->addComponent<Transform>(Vector2D(posX + 3 * w / 2 + 300, h + offsetY), w, h);
	Boton->addComponent<Image>(&sdlutils().images().at("star"));
	Boton->getComponent<Image>()->setTexture(&sdlutils().images().at("vacio"));
	Boton->addComponent<ButtonPlay>(gsm, &sdlutils().images().at("play"), play);

	auto* p1 = mngr_->addEntity(RenderLayer::Interfaz);
	p1->addComponent<Transform>(Vector2D(85, sdlutils().height() / 2 - 250), 150, 150);
	auto* img1 = p1->addComponent<Image>(&sdlutils().images().at("p1v"));
	auto* p2 = mngr_->addEntity(RenderLayer::Interfaz);
	p2->addComponent<Transform>(Vector2D(85, sdlutils().height() / 2 + 75), 150, 150);
	auto* img2 = p2->addComponent<Image>(&sdlutils().images().at("p2v"));
	if (gsm->getCharSel()->getEquipo() == 0) {
		equipo = "circuloA";
		img1->setTexture(&sdlutils().images().at("p1v"));
		img2->setTexture(&sdlutils().images().at("p2nv"));
	}
	else {
		equipo = "circuloR";
		img1->setTexture(&sdlutils().images().at("p1nv"));
		img2->setTexture(&sdlutils().images().at("p2v"));
	}
}

CharacterSelectionState::~CharacterSelectionState(){}

void CharacterSelectionState::update() {
	mngr_->update();
	mngr_->refresh();

	sdlutils().clearRenderer();
	mngr_->render();
	renderSelected();
	sdlutils().presentRenderer();
}

void CharacterSelectionState::renderSelected() {
	SDL_Rect dest;
	dest.x = 260; dest.y = sdlutils().height() - 160;
	dest.w = 150; dest.h = 150;

	for (Texture* t : personajesSelected) {

		if (equipo == "circuloA")t->render(dest);
		else t->render(build_sdlrect(0.0, 0.0, 500.0, 500.0), dest, 0, nullptr, SDL_FLIP_HORIZONTAL);
		dest.x += 260;
	}
	dest.x = 260;
	for (int i = 1; i <= 6; i++) {
		sdlutils().images().at(equipo).render(dest);
		dest.x += 260;
	}
}

void CharacterSelectionState::addCharacterSelected(Texture* tex) {
	personajesSelected.emplace_back(tex);
}

void CharacterSelectionState::removeCharacterSelected(Texture* tex) {
	vector<Texture*>::iterator it2;
	for (vector<Texture*>::iterator it = personajesSelected.begin(); it < personajesSelected.end(); it++) {
		if (*it == tex) {
			it2 = it;
		}
	}
	personajesSelected.erase(it2);
}

void CharacterSelectionState::play(GameStateMachine* gsm) {
	if (!gsm->isOnline())
	{
		if (gsm->getCharSel()->getEquipo() == 0) {
			gsm->getCharSel()->setEquipo(1);
			gsm->getCharSel()->updateCont();
			gsm->changeState(new CharacterSelectionState(gsm));
		}
		else gsm->getCharSel()->play(gsm);
	}
	else
	{
		CharacterSelectionState* characterSelectionState = static_cast<CharacterSelectionState*>(gsm->currentState());
		if (characterSelectionState->getSelfSelectd()) return;
		gsm->getNetworkManager()->sendDeckReady();
		characterSelectionState->setSelfHasSelected();
		characterSelectionState->checkGameReady(gsm);
		//TODO quitar botón y poner mensaje de esperar al otro jugador
	}

}

void CharacterSelectionState::checkGameReady(GameStateMachine* gsm)
{
	CharacterSelectionState* characterSelectionState = static_cast<CharacterSelectionState*>(gsm->currentState());
	if (characterSelectionState->getEnemySelected() && characterSelectionState->getSelfSelectd()) gsm->getCharSel()->play(gsm);
	//else std:: << gsm->getNetworkManager()->isMaster() ? "Master esta esperando\n" : "El client esta esperando\n";
}

// ALQUIMISTA
void CharacterSelectionState::updateAlquimista(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Alquimista);
}

// ARQUITECTA
void CharacterSelectionState::updateArquitecta(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Arquitecta);
}

// BOMBA
void CharacterSelectionState::updateBomba(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Bomba);
}

// CAZADOR
void CharacterSelectionState::updateCazador(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Cazador);
}

// DRUIDA
void CharacterSelectionState::updateDruida(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Druida);
}

// ESQUELETO
void CharacterSelectionState::updateEsqueleto(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Esqueleto);
}

// GOLEM
void CharacterSelectionState::updateGolem(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Golem);
}

// KIRIN
void CharacterSelectionState::updateKirin(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Kirin);
}

// LOBO
void CharacterSelectionState::updateLobo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Lobo);
}

// MONAGUILLO
void CharacterSelectionState::updateMonaguillo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Monaguillo);
}

// PICARA
void CharacterSelectionState::updatePicara(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Picara);
}

// TANQUE
void CharacterSelectionState::updateTanque(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Tanque);
}

// VIKINGO
void CharacterSelectionState::updateVikingo(GameStateMachine* gsm) {
	gsm->getCharSel()->updatePersonaje(Vikingo);
}
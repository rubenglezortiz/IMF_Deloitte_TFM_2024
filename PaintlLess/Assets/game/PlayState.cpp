#include "PlayState.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SoundEffect.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../components/GameMap.h"
#include "../components/Movimiento.h"
#include "../components/Health.h"
#include "../components/PointOnImage.h"
#include "../components/Ability_Architect.h"
#include "../components/Ability.h"
#include "../components/Ability_Bomb.h"
#include "../components/Ability_Golem.h"
#include "../components/Ability_Kirin.h"
#include "../components/Ability_Rogue.h"
#include "../components/Ability_Viking.h"
#include "../components/Ability_Druid.h"
#include "../components/Attack.h"
#include "../components/DeckSpawn.h"
#include "../components/Interfaz.h"
#include "../components/Transform2.h"
#include "../components/MenuButton.h"

#include "../game/Values.h"
#include "FinState.h"
#include "GameStateMachine.h"
#include "Network.h"
#include "../components/EntityFactory.h"
#include "../components/ComponentBuffer.h"

#include "../../checkML.h"

PlayState::PlayState(GameStateMachine* gsm, vector<bool> charss, vector<bool> charss2, int mapa, int tileset) : GameState(gsm) {

	//Obtener net
	net = gsm->getNetworkManager();

	// Creación interfaz
	auto* fondo = mngr_->addEntity(RenderLayer::Fondo);
	fondo->addComponent<Transform>(Vector2D(), sdlutils().width(), sdlutils().height());

	fondo->addComponent<Image>(&sdlutils().images().at("tablero" + to_string(tileset)));

	// Creacion GameMap
	auto* m = mngr_->addEntity(RenderLayer::Tablero);
	m->addComponent<GameMap>(mapa, tileset, this);
	mngr_.get()->setHandler<Mapa>(m);
	mapa_ = m->getComponent<GameMap>();
	m->addComponent<Interfaz>();

	for (int i = 0; i < charss.size(); ++i) {
		if (charss[i]) ch1.push_back(true);
		else ch1.push_back(false);
		if (charss2[i]) ch2.push_back(true);
		else ch2.push_back(false);
	}

	// Creación boardManager
	Entity* boardManager = mngr_->addEntity(RenderLayer::Tablero2);
	boardManager->addComponent<PointOnImage>(&sdlutils().images().at("selector"));

	mngr_.get()->setHandler<BoardManager>(boardManager);

	//boardManager->getComponent<MovementShader>()->getValues();
	mazoEquipo();
	//createTanque(Segundo);
	sdlutils().showCursor();
	//pasaTurno();

	// Creacion Botón pasar turno
	auto* botonTurno = mngr_->addEntity(RenderLayer::Interfaz);
	botonTurno->addComponent<Transform2>(Vector2D(sdlutils().width() - 305, sdlutils().height() - 120), 225, 100);
	botonTurno->addComponent<Image>(&sdlutils().images().at("botonT"));
	shaderManager = mngr_->addEntity(RenderLayer::Tablero2);
	ComponentBuffer* buffer = shaderManager->addComponent<ComponentBuffer>();

	abililyShader = new UniversalShader(mapa_);
	movementShader = new UniversalShader(mapa_);
	attackShader = new UniversalShader(mapa_);

	movementShader->setTexture(&sdlutils().images().at("MovShader"));
	attackShader->setTexture(&sdlutils().images().at("selectorA"));
	//La textura de abilityShader la cambia AbilitySegun si es o no enemigo

	buffer->addComponent(abililyShader);
	buffer->addComponent(movementShader);
	buffer->addComponent(attackShader);

	switch (tileset) {
	case 1:
		music = "field";
		break;
	case 2:
		music = "ice";
		break;
	case 3:
		music = "castle";
		break;
	}
	sdlutils().soundEffects().at(music).play(1000);
	sdlutils().soundEffects().at(music).setChunkVolume(sdlutils().volumeMUS());
}

PlayState::~PlayState() {
	sdlutils().soundEffects().at(music).haltChannel();
}

void PlayState::mazoEquipo() {
	int x = 1;
	for (int i = 0; i < ch1.size(); ++i) {
		if (ch1[i]) {
			createMazo(i, x, 0);
			x++;
		}
	}
	x = 1;
	for (int i = 0; i < ch2.size(); ++i) {
		if (ch2[i]) {
			createMazo(i, x, 1);
			x++;
		}
	}
}

void PlayState::createMazo(int n, int x, int equipo) {
	if (equipo == 1)
		x = -sdlutils().width();
	auto* boton = mngr_->addEntity(RenderLayer::Personajes);
	boton->addComponent<Transform2>(Vector2D((x + 0.5) * sdlutils().width() / 9, sdlutils().height() - 120), sdlutils().width() / 9, 100);

	std::string imagen;
	if (equipo == 1) imagen = "R";
	else imagen = "A";

	switch (n) {
	case Alquimista:
		boton->addComponent<Image>(&sdlutils().images().at("alquimistaMazo" + imagen));
		boton->addComponent<DeckSpawn>(Alquimista);
		break;
	case Arquitecta:
		boton->addComponent<Image>(&sdlutils().images().at("arquitectaMazo" + imagen));
		boton->addComponent<DeckSpawn>(Arquitecta);
		break;
	case Bomba:
		boton->addComponent<Image>(&sdlutils().images().at("bombaMazo" + imagen));
		boton->addComponent<DeckSpawn>(Bomba);
		break;
	case Cazador:
		boton->addComponent<Image>(&sdlutils().images().at("cazadorMazo" + imagen));
		boton->addComponent<DeckSpawn>(Cazador);
		break;
	case Druida:
		boton->addComponent<Image>(&sdlutils().images().at("druidaMazo" + imagen));
		boton->addComponent<DeckSpawn>(Druida);
		break;
	case Esqueleto:
		boton->addComponent<Image>(&sdlutils().images().at("esqueletoMazo" + imagen));
		boton->addComponent<DeckSpawn>(Esqueleto);
		break;
	case Golem:
		boton->addComponent<Image>(&sdlutils().images().at("golemMazo" + imagen));
		boton->addComponent<DeckSpawn>(Golem);
		break;
	case Kirin:
		boton->addComponent<Image>(&sdlutils().images().at("kirinMazo" + imagen));
		boton->addComponent<DeckSpawn>(Kirin);
		break;
	case Lobo:
		boton->addComponent<Image>(&sdlutils().images().at("loboMazo" + imagen));
		boton->addComponent<DeckSpawn>(Lobo);
		break;
	case Monaguillo:
		boton->addComponent<Image>(&sdlutils().images().at("monaguilloMazo" + imagen));
		boton->addComponent<DeckSpawn>(Monaguillo);
		break;
	case Picara:
		boton->addComponent<Image>(&sdlutils().images().at("picaraMazo" + imagen));
		boton->addComponent<DeckSpawn>(Picara);
		break;
	case Tanque:
		boton->addComponent<Image>(&sdlutils().images().at("tanqueMazo" + imagen));
		boton->addComponent<DeckSpawn>(Tanque);
		break;
	case Vikingo:
		boton->addComponent<Image>(&sdlutils().images().at("vikingoMazo" + imagen));
		boton->addComponent<DeckSpawn>(Vikingo);
		break;
	}
	if (equipo == 1) boton->setGroup<Mazo1>(true);
	else boton->setGroup<Mazo2>(true);
}

void PlayState::moveMazo() {
	int pos = -sdlutils().width();
	float i = 1.5;
	if (jugadorActual == Primero) {
		for (Entity* e : mngr_->getEnteties()) {
			if (e->hasGroup<Mazo2>()) {
				e->getComponent<Transform2>()->getPos().setX(pos);
				pos -= e->getComponent<Transform2>()->getW();
			}
			if (e->hasGroup<Mazo1>()) {
				e->getComponent<Transform2>()->getPos().setX(i * sdlutils().width() / 9);
				i++;
			}
		}
	}
	else {
		for (Entity* e : mngr_->getEnteties()) {
			if (e->hasGroup<Mazo2>()) {
				e->getComponent<Transform2>()->getPos().setX(i * sdlutils().width() / 9);
				i++;
			}
			if (e->hasGroup<Mazo1>()) {
				e->getComponent<Transform2>()->getPos().setX(pos);
				pos -= e->getComponent<Transform2>()->getW();
			}
		}
	}
}

void PlayState::update()
{
	CheckPasarTurno();
	GameState::update();
}

void PlayState::_net_moveChar(Vector2D charPosInMap, Vector2D dest)
{
	Entity* entity = mapa_->getCharacter(mapa_->SDLPointToMapCoords(charPosInMap));
	if (entity != nullptr)
	{
		Movimiento* movement = entity->getComponent<Movimiento>();
		movement->MoveCharacter(charPosInMap, dest);
	}
}

void PlayState::_net_abilityChar(Vector2D charPosInMap, Vector2D dest)
{
	charPosInMap = mapa_->SDLPointToMapCoords(charPosInMap);
	Entity* entity = mapa_->getCharacter(charPosInMap);
	if (entity != nullptr)
	{
		Ability* characterAbilty = entity->getComponent<Ability>();
		characterAbilty->TryExecuteAbility(dest.getX(), dest.getY());
	}
}

void PlayState::_net_attackChar(Vector2D charPosInMap, Vector2D dest, int dmg)
{
	Entity* atacante = mapa_->getCharacter(charPosInMap);
	Entity* atacado = mapa_->getCharacter(dest);
	if (atacante != nullptr)
	{
		atacante->getComponent<Attack>()->attackSound();
	}
	if (atacado != nullptr)
	{
		Health* life = atacado->getComponent<Health>();
		if (life != nullptr) life->hit(dmg);
	}
}

void PlayState::CheckPasarTurno()
{
	int mX = ih().getMousePos().first;
	int mY = ih().getMousePos().second;
	if (ih().isKeyDown(SDLK_SPACE) || (mX >= (sdlutils().width() - 330 + 20) && mX <= (sdlutils().width() - 330 + 245) && mY >= (sdlutils().height() - 120) && mY <= (sdlutils().height() - 120 + 100) &&
		ih().getMouseButtonState(ih().LEFT))) {
		if (!gameStateMachine->isOnline())
		{
			pasaTurno();
		}
		else if (gameStateMachine->isOnline() &&
			(jugadorActual == Primero && !net->isMaster() ||
				jugadorActual == Segundo && net->isMaster()))
		{
			pasaTurno();
			net->sendChangeTurno();
		}
	}
}

void PlayState::pasaTurno() {
	accionesPorTurno = MAX_ACCIONES;

	if (jugadorActual == Primero) {
		jugadorActual = Segundo;
		if (mana_1 + INCREMENTO_MANA >= MAX_MANA)
			mana_1 = MAX_MANA;
		else
			mana_1 += INCREMENTO_MANA;
		moveMazo();
	}
	else {
		jugadorActual = Primero;
		if (mana_2 + INCREMENTO_MANA >= MAX_MANA)
			mana_2 = MAX_MANA;
		else
			mana_2 += INCREMENTO_MANA;
		moveMazo();
	}
	checkEndGame();

	mngr_->finTurno();
}

void PlayState::checkEndGame()
{
	if (turnosActuales + 1 > MAX_TURNOS * 2) {
		int numCasillasPintables = mapa_->getNumCasPintables();
		int casRojo = getPintado1() * 100 / numCasillasPintables;
		int casAzul = getPintado2() * 100 / numCasillasPintables;
		int ganador, porcentaje;
		if (casRojo > casAzul) {
			ganador = 0;
			porcentaje = casRojo;
		}
		else if (casRojo < casAzul) {
			ganador = 1;
			porcentaje = casAzul;
		}
		else {
			ganador = 2;
			porcentaje = casRojo;
		}
		gameStateMachine->pushState(new FinState(gameStateMachine, ganador, porcentaje));
	}

	else turnosActuales++;
}

void PlayState::_net_endGame()
{
	int numCasillasPintables = mapa_->getNumCasPintables();
	int casRojo = getPintado1() * 100 / numCasillasPintables;
	int casAzul = getPintado2() * 100 / numCasillasPintables;
	int ganador, porcentaje;
	if (turnosActuales == MAX_TURNOS)
	{
		if (casRojo > casAzul) {
			ganador = 0;
			porcentaje = casRojo;
		}
		else if (casRojo < casAzul) {
			ganador = 1;
			porcentaje = casAzul;
		}
		else {
			ganador = 2;
			porcentaje = casRojo;
		}
	}
	else {
		ganador = getCurrentPlayer() == Equipo::Primero ? 1 : 0;
		porcentaje = getPorcentajeSurrender();
	}
	gameStateMachine->pushState(new FinState(gameStateMachine, ganador, porcentaje));
}

int PlayState::getPorcentaje() {
	if (jugadorActual == Primero)
		return (pintado_1 * 100) / mapa_->getNumCasPintables();
	else
		return (pintado_2 * 100) / mapa_->getNumCasPintables();
}

int PlayState::getPorcentajeSurrender() {
	if (jugadorActual != Primero)
		return (pintado_1 * 100) / mapa_->getNumCasPintables();
	else
		return (pintado_2 * 100) / mapa_->getNumCasPintables();
}

bool PlayState::restaMana(int m, int& mana)
{
	if (mana - m >= 0) {
		mana -= m;
		return true;
	}
	else
		return false;
}

bool PlayState::manaSuficiente(int m, int mana) const {
	return (mana - m >= 0);
}
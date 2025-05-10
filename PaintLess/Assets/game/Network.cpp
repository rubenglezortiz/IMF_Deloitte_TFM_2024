// This file is part of the course TPV2@UCM - Samir Genaim

#include "Network.h"

#include <SDL_net.h>

#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"
#include "../game/CharacterSelectionState.h"
#include "../game/PlayState.h"
#include "../components/EntityFactory.h"
#include "../components//GameMap.h"
#include <iostream>

Network::Network() : host_(nullptr), port_(2000),
isMaster_(false), isGameReday_(false), id_(0), conn_(), p_(nullptr), otherPlayerAddress_(), localPlayerName_("a"), remotePlayerName_("N/A"),
lastTimeActive_(0), managerState_(nullptr) { }


Network::~Network() {

	if (conn_) {
		DissConnectMsg* m = static_cast<DissConnectMsg*>(m_);
		m->_type = _DISCONNECTED_;
		m->id = id_;
		p_->len = sizeof(DissConnectMsg);
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);
	}

	// close the connection
	if (conn_)
		SDLNet_UDP_Close(conn_);

	// free the packet
	if (p_) {
		SDLNet_FreePacket(p_);
	}

	// close SDLNet
	SDLNet_Quit();
}

void Network::init(GameStateMachine* gameStateMachine) {
	gsm = gameStateMachine;
	// Initialise SDLNet
	if (SDLNet_Init() < 0) {
		throw SDLNet_GetError();
	}

	// allocate the packet to be used for sending data
	p_ = SDLNet_AllocPacket(100);
	m_ = reinterpret_cast<NetworkMessage*>(p_->data);

	if (host_ == nullptr) { // if started as a master player
		// we use id 0, and open a socket to send/receive messages
		isMaster_ = true;
		id_ = 0;
		conn_ = SDLNet_UDP_Open(port_);

		if (true) {
			isMaster_ = false;
			host_ = "localhost";
			ifstream file = ifstream();
			string ip;
			file.open("./ip/ip.txt");
			getline(file, ip);
			file.close();
			host_ = ip.c_str();


			//		id_ = 1;
			conn_ = SDLNet_UDP_Open(0);
			if (!conn_)
				throw SDLNet_GetError();

			std::cout << "Trying to connect to other player at " << host_ << ":"
				<< port_ << std::endl;

			// resolve the host name into an IPAdrress
			if (SDLNet_ResolveHost(&otherPlayerAddress_, host_, port_) < 0) {
				throw SDLNet_GetError();

			}


			// send a message asking to play
			PlayRequestMsg* m = static_cast<PlayRequestMsg*>(m_);
			m->_type = _I_WANT_TO_PLAY_;
			memset(m->name, 0, 10);
			auto size =
				localPlayerName_.length() > 9 ? 9 : localPlayerName_.length();
			memcpy(m->name, localPlayerName_.c_str(), size);
			p_->len = sizeof(PlayRequestMsg);
			p_->address = otherPlayerAddress_;
			SDLNet_UDP_Send(conn_, -1, p_);

			// we use socket set to allow waiting for response instead of just looping
			SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
			SDLNet_UDP_AddSocket(socketSet, conn_);

			// wait for response
			if (SDLNet_CheckSockets(socketSet, 3000)) {
				if (SDLNet_SocketReady(conn_)) {
					if (SDLNet_UDP_Recv(conn_, p_) > 0) {

						if (m_->_type == _WELCOME_) {
							isGameReday_ = true;
							WelcomeMsg* m = static_cast<WelcomeMsg*>(m_);
							remotePlayerName_ = std::string(
								reinterpret_cast<char*>(m->name));
							id_ = m->id;
							names_[id_] = localPlayerName_;
							names_[1 - id_] = remotePlayerName_;

						}
					}
				}
			}

			// free the socket set, won't be used anymore
			SDLNet_FreeSocketSet(socketSet);

			// if did not succeed to connect, throw an exception
			if (!isGameReday_)
				throw "Failed to connect!";
		}
	}
	else { // if started as  other player

	 // we use id 1, and open a socket to send/receive messages


	}

}

void Network::update() {

	m_->_type = _ACTIVE_;
	p_->len = sizeof(NetworkMessage);
	p_->address = otherPlayerAddress_;
	SDLNet_UDP_Send(conn_, -1, p_);



	// in each iteration we poll all pending message and process them
	while (SDLNet_UDP_Recv(conn_, p_) > 0) {
		lastTimeActive_ = SDL_GetTicks();
		switch (m_->_type) {

		case _I_WANT_TO_PLAY_: {
			// we accept the connection if the player is the master, and no other player is connected
			if (isMaster_ && !isGameReday_) {
				PlayRequestMsg* m = static_cast<PlayRequestMsg*>(m_);
				otherPlayerAddress_ = p_->address;
				remotePlayerName_ = std::string(
					reinterpret_cast<char*>(m->name));
				names_[1 - id_] = remotePlayerName_;
				WelcomeMsg* mr = static_cast<WelcomeMsg*>(m_);

				mr->_type = _WELCOME_;
				auto size =
					localPlayerName_.size() > 9 ?
					9 : localPlayerName_.size();
				memcpy(mr->name, localPlayerName_.c_str(), size);
				mr->id = 1 - id_;
				p_->len = sizeof(WelcomeMsg);
				SDLNet_UDP_Send(conn_, -1, p_);
				isGameReday_ = true;
			}
			break;
		}

		case _DECK_RECEIVED_: {
			CharacterSelectionState* characterSelectionState = dynamic_cast<CharacterSelectionState*>(gsm->currentState());
			if (characterSelectionState == nullptr) return;

			characterSelectionState->setEnemySelected();
			characterSelectionState->checkGameReady(gsm);

			break;
		}

		case _CLIENT_GAME_:
		{
			std::cout << "Client has received game\n";
			CreateGameMessage* m = static_cast<CreateGameMessage*>(m_);
			gsm->getCharSel()->clientPlay(gsm, m->mapa, m->tileset);
			break;
		}

		case _TURN_CHANGE_:
		{
			PlayState* playState = gsm->getPlayState();
			if (playState != nullptr)
			{
				playState->pasaTurno();
			}
			break;
		}

		case _MOVE_CHARACTER_: {
			PlayState* playState = gsm->getPlayState();
			ActionMessage* m = static_cast<ActionMessage*>(m_);
			if (playState != nullptr)
				playState->_net_moveChar(Vector2D(m->mapX, m->mapY), Vector2D(m->posX, m->posY));
			break;
		}

		case _SPAWN_CHARACTER_: {

			SpawnMessage* m = static_cast<SpawnMessage*>(m_);
			PlayState* playState = gsm->getPlayState();
			if (playState != nullptr)
			{
				int equipo = playState->getCurrentPlayer() == 0 ? 1 : 0;
				//int equipo = playState->getCurrentPlayer();
				EntityFactory::createCharacter(playState->getMapa()->getEntity()->getMngr(), playState->getMapa(), playState, m->personaje, equipo, Vector2D((float)m->posX, (float)m->posY));
			}
			break;
		}
		case _EXECUTE_ABILTY_: {

			PlayState* playState = gsm->getPlayState();
			ActionMessage* m = static_cast<ActionMessage*>(m_);
			if (playState != nullptr)
				playState->_net_abilityChar(Vector2D(m->mapX, m->mapY), Vector2D(m->posX, m->posY));
			break;
		}

		case _FINISH_GAME_:
		{
			endGame();
			break;
		}

		case _ATTACK_MESSAGE_: {
			PlayState* playState = gsm->getPlayState();
			AttackMessage* m = static_cast<AttackMessage*>(m_);
			if (playState != nullptr)
				playState->_net_attackChar(Vector2D(m->mapX, m->mapY), Vector2D(m->posX, m->posY), m->dmg);
			break;
		}

		case _DISCONNECTED_: {
			//endGame();
		}
		}
	}

	//if (isGameReday_ && SDL_GetTicks() - lastTimeActive_ > 3000) {
	//	isGameReday_ = false;
	//	names_[1 - id_] = remotePlayerName_ = "N/A";
	//	if (!isMaster_) {
	//		SDLNet_UDP_Close(conn_);
	//		conn_ = SDLNet_UDP_Open(port_);
	//		isMaster_ = true;
	//	}

	//}

}

void Network::sendDeckReady()
{
	// if the other player is not connected do nothing
	if (!isGameReday_)
		return;

	// we prepare a message that includes all information
	NetworkMessage* m = static_cast<NetworkMessage*>(m_);
	m->_type = _DECK_RECEIVED_;

	// set the message length and the address of the other player
	p_->len = sizeof(NetworkMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendCreateGame(int mapa, int tileset)
{
	// if the other player is not connected do nothing
	if (!isGameReday_)
		return;

	// we prepare a message that includes all information
	CreateGameMessage* m = static_cast<CreateGameMessage*>(m_);
	m->_type = _CLIENT_GAME_;
	m->mapa = mapa;
	m->tileset = tileset;

	// set the message length and the address of the other player
	p_->len = sizeof(CreateGameMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendChangeTurno()
{
	// if the other player is not connected do nothing
	if (!isGameReday_)
		return;

	// we prepare a message that includes all information
	NetworkMessage* m = static_cast<NetworkMessage*>(m_);
	m->_type = _TURN_CHANGE_;

	// set the message length and the address of the other player
	p_->len = sizeof(NetworkMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendSpawnCharacter(int personaje, int posX, int posY)
{
	// if the other player is not connected do nothing
	if (!isGameReday_)
		return;

	// we prepare a message that includes all information
	SpawnMessage* m = static_cast<SpawnMessage*>(m_);
	m->_type = _SPAWN_CHARACTER_;
	m->personaje = personaje;
	m->posX = posX;
	m->posY = posY;

	// set the message length and the address of the other player
	p_->len = sizeof(SpawnMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendActionMessage(int&& mapX, int&& mapY, int&& posX, int&& posY, MsgType&& mensaje)
{
	// if the other player is not connected do nothing
	if (!isGameReday_)return;

	// we prepare a message that includes all information
	ActionMessage* m = static_cast<ActionMessage*>(m_);
	m->_type = mensaje;
	m->mapX = mapX;
	m->mapY = mapY;
	m->posX = posX;
	m->posY = posY;

	// set the message length and the address of the other player
	p_->len = sizeof(ActionMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendMoveMessage(int&& mapX, int&& mapY, int&& posX, int&& posY)
{
	sendActionMessage(std::forward<int>(mapX), std::forward<int>(mapY),
		std::forward<int>(posX), std::forward<int>(posY), _MOVE_CHARACTER_);
}

void Network::sendExecuteAbility(int&& mapX, int&& mapY, int&& posX, int&& posY)
{
	sendActionMessage(std::forward<int>(mapX), std::forward<int>(mapY),
		std::forward<int>(posX), std::forward<int>(posY), _EXECUTE_ABILTY_);
}

void Network::sendAttack(int&& mapX, int&& mapY, int&& posX, int&& posY, int&& dmg)
{
	// if the other player is not connected do nothing
	if (!isGameReday_)return;

	// we prepare a message that includes all information
	AttackMessage* m = static_cast<AttackMessage*>(m_);
	m->_type = _ATTACK_MESSAGE_;
	m->mapX = mapX;
	m->mapY = mapY;
	m->posX = posX;
	m->posY = posY;
	m->dmg = dmg;


	// set the message length and the address of the other player
	p_->len = sizeof(AttackMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::sendEndGame()
{
	// if the other player is not connected do nothing
	if (!isGameReday_)return;

	// we prepare a message that includes all information
	NetworkMessage* m = static_cast<NetworkMessage*>(m_);
	m->_type = _FINISH_GAME_;

	// set the message length and the address of the other player
	p_->len = sizeof(NetworkMessage);
	p_->address = otherPlayerAddress_;

	// send the message
	SDLNet_UDP_Send(conn_, -1, p_);
}

void Network::restartConnection()
{
	isGameReday_ = false;
	host_ = nullptr;
	isMaster_ = false;
	gsm->setOnline(false);

	if (conn_)
		SDLNet_UDP_Close(conn_);

	// close SDLNet
	SDLNet_Quit();
}

void Network::endGame()
{
	restartConnection();
	PlayState* playState = dynamic_cast<PlayState*>(gsm->currentState());
	gsm->restartCharacterSelection();
	if (playState != nullptr) playState->_net_endGame();
	else
	{
		gsm->popState();
		gsm->refresh();
		playState = dynamic_cast<PlayState*>(gsm->currentState());
		if (playState != nullptr)
		{
			playState->_net_endGame();
		}
	}
}

// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "network_types.h"

#pragma pack(push,1)

enum MsgType : uint8_nt {
	_NONE_,
	_I_WANT_TO_PLAY_,
	_WELCOME_,
	_DISCONNECTED_, //
	_ACTIVE_, //
	_DECK_RECEIVED_, //
	_CLIENT_GAME_, //
	_TURN_CHANGE_, //
	_SPAWN_CHARACTER_, //
	_MOVE_CHARACTER_, //
	_EXECUTE_ABILTY_,
	_ATTACK_MESSAGE_,
	_FINISH_GAME_
};

struct NetworkMessage {
	uint8_nt _type;
};

struct SpawnMessage : NetworkMessage
{
	uint8_nt personaje;
	uint8_nt posX;
	uint8_nt posY;
};

struct ActionMessage : NetworkMessage
{
	uint16_nt mapX;
	uint16_nt mapY;
	uint16_nt posX;
	uint16_nt posY;
};

struct AttackMessage : ActionMessage
{
	uint16_nt dmg;
};

struct CreateGameMessage : NetworkMessage
{
	uint8_nt mapa;
	uint8_nt tileset;
};

struct DissConnectMsg : NetworkMessage {
	uint8_nt id;
};

struct PlayRequestMsg : NetworkMessage {
	uint8_nt name[10];
};

struct WelcomeMsg : NetworkMessage {
	uint8_nt id;
	uint8_nt name[10];
};

#pragma pack(pop)
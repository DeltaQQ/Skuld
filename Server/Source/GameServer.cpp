#pragma once
#include "GameServer.h"

GameServer::GameServer(uint16_t port)
	:
	Net::Server<GameMsg>(port)
{
}

void GameServer::on_message()
{

}
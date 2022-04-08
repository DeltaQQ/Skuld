#pragma once
#include "GameServer.h"

GameServer::GameServer(uint16_t port)
	:
	Net::Server<GameMsg>(port)
{
}

void GameServer::on_message(std::shared_ptr<Net::Connection<GameMsg>> client, Net::Message<GameMsg>& message)
{

}

void GameServer::on_client_connect(std::shared_ptr<Net::Connection<GameMsg>> client)
{

}

void GameServer::on_client_disconnect(std::shared_ptr<Net::Connection<GameMsg>> client)
{

}
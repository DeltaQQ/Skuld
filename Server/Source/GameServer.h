#pragma once
#include <Network/Server.h>

#include "GameMsg.h"

class GameServer : public Net::Server<GameMsg>
{
public:
	GameServer(uint16_t port);
	~GameServer() override = default;

	void on_message(std::shared_ptr<Net::Connection<GameMsg>> client, Net::Message<GameMsg>& message) override;

	void on_client_connect(std::shared_ptr<Net::Connection<GameMsg>> client) override;

	void on_client_disconnect(std::shared_ptr<Net::Connection<GameMsg>> client) override;
};
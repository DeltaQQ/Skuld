#pragma once
#include <Network/Server.h>

#include "GameMsg.h"

class GameServer : public Net::Server<GameMsg>
{
public:
	GameServer(uint16_t port);
	~GameServer() override = default;

	void on_message(Net::Message<GameMsg>& message) override;
};
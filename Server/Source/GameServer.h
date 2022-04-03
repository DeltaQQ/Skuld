#pragma once
#include <Network/Server.h>

enum class GameMsg
{
	UpdatePlayer
};

class GameServer : public Net::Server<GameMsg>
{
public:
	GameServer(uint16_t port);
	~GameServer() override = default;

	void on_message() override;
};
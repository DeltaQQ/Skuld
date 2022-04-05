#pragma once
#include <Network/Client.h>
#include <Window/Window.h>

#include "GameMsg.h"

class GameClient : Net::Client<GameMsg>
{
public:
	GameClient() = default;
	~GameClient() = default;

	void start();

	void on_message(Net::Message<GameMsg>& message) override;

private:
	Window m_window;
};
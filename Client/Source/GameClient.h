#pragma once
#include <Network/Client.h>
#include <Window/Window.h>

#include "GameMsg.h"

#include "Authentication.h"

class GameClient : Net::Client<GameMsg>
{
public:
	GameClient() = default;
	~GameClient() = default;

	void start();

private:
	Window m_window;
	Authentication m_authentication;
};
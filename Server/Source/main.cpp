#pragma once
#include <iostream>

#include "GameServer.h"

int main()
{
	GameServer server(8000);
	server.start();

	while (true)
	{
		server.update();
	}

	return 0;
}
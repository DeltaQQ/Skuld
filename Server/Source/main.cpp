#pragma once
#include <iostream>

#include "GameServer.h"
#include "Database.h"

int main()
{
	Database database;

	GameServer server(51500);
	server.start();

	while (true)
	{
		server.update();
	}

	return 0;
}
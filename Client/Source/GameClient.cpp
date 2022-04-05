#include "GameClient.h"

void GameClient::start()
{
	connect("2a02:8071:2ae:9600:f10b:4c01:97d4:db2c", 51500);

	m_window.create(1280, 720, "Skuld");

	while (m_window)
	{

	}
}

void GameClient::on_message(Net::Message<GameMsg>& message)
{

}
#include "GameClient.h"

#include <iostream>
#include <fstream>
#include <json.hpp>

void GameClient::start()
{
	std::string email;
	std::string password;

	if (!m_authentication.is_signed_in())
		do
		{
			std::cout << "E-Mail: ";
			std::cin >> email;
			std::cout << "Password: ";
			std::cin >> password;
		} while (!m_authentication.sign_in(email, password));

		if (!m_authentication.is_verified())
		{
			std::cout << "Please verify your email" << std::endl;
			return;
		}

	std::ifstream ifstream("connection.json");
	nlohmann::json json;
	ifstream >> json;

	connect_to_server(json["ip"], json["port"], m_authentication.get_user_id());

	m_window.create(1280, 720, "Skuld");

	while (m_window)
	{

	}
}

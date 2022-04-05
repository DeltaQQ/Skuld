#include "Database.h"

#include <iostream>
#include <fstream>
#include <json.hpp>

Database::Database()
	:
	m_connection(nullptr)
{
	try
	{
		std::ifstream ifstream("db_connection.json");

		nlohmann::json json;

		ifstream >> json;

		std::string credentials = json["connection"];

		m_connection = new pqxx::connection(credentials);

		std::cout << "[Database] Connected!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Database::~Database()
{
	delete m_connection;

	std::cout << "[Database] Disconnected!" << std::endl;
}

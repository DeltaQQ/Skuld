#pragma once
#include <iostream>

#include <Network/Message.h>
#include <Window/Window.h>

int main()
{
	asio::error_code error_code;

	asio::io_context context;

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("::1", error_code), 80);

	if (error_code)
	{
		std::cout << "make_address failed: " << error_code.message() << std::endl;
	}

	asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, error_code);

	if (!error_code)
	{
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Connection failed: " << error_code.message() << std::endl;
	}

	Window window(1280, 720, "Skuld");

	while (window)
	{
	}

	return 0;
}
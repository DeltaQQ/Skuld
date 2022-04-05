#pragma once

#include <Data Structures/tsqueue.h>

#include "Common.h"
#include "Message.h"

namespace Net
{
	template <typename T>
	class Client
	{
	public:
		Client()
			:
			m_socket(asio::ip::tcp::socket(m_context))
		{}

		virtual ~Client()
		{
			disconnect();
		}

		virtual void on_message(Net::Message<T>& message) {}

		void connect(const std::string& host, uint16_t port)
		{
			try
			{
				asio::ip::tcp::resolver resolver(m_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				asio::async_connect(m_socket, endpoints,
					[this](std::error_code error_code, asio::ip::tcp::endpoint endpoint)
					{
						if (!error_code)
						{
							std::cout << "Connected!" << std::endl;
						}
						else
						{
							std::cout << error_code.message() << std::endl;
						}
					});

				m_context_thread = std::thread([this]() { m_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "[Connection Failed]: " << e.what() << std::endl;
			}
		}

		void disconnect()
		{
			if (m_socket.is_open())
				asio::post(m_context, [this]() { m_socket.close(); });

			if (m_context_thread.joinable())
				m_context_thread.join();
		}

	private:
		asio::io_context m_context;
		std::thread m_context_thread;

		asio::ip::tcp::socket m_socket;

		tsqueue<Message<T>> m_message_queue;
	};
}
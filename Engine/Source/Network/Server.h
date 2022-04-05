#pragma once

#include <Data Structures/tsqueue.h>

#include "Message.h"

namespace Net
{
	template <typename T>
	class Server
	{
	public:
		Server(uint16_t port)
			:
			m_acceptor(m_context, asio::ip::tcp::endpoint(get_local_ipv6_address(), port))
		{
		}

		virtual ~Server()
		{
			stop();
		}

		bool start()
		{
			try
			{
				wait_for_client_connection();

				m_context_thread = std::thread([this]() { m_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << "[Server] " << e.what() << std::endl;
				return false;
			}

			std::cout << "[Server] Started!" << std::endl;
			return true;
		}

		void stop()
		{
			m_context.stop();

			if (m_context_thread.joinable())
				m_context_thread.join();

			std::cout << "[Server] Stopped!" << std::endl;
		}

		void update()
		{
			m_message_queue.wait();

			while (!m_message_queue.empty())
			{
				auto message = m_message_queue.pop_front();

				on_message(message);
			}
		}

	protected:
		virtual void on_message(Message<T>& message) {}

	private:
		void wait_for_client_connection()
		{
			m_acceptor.async_accept(
				[this](std::error_code error_code, asio::ip::tcp::socket socket)
				{
					if (!error_code)
					{
						std::cout << "[Server] New Connection: " << socket.remote_endpoint() << std::endl;
					}
					else
					{
						std::cout << "[Server] Connection Error: " << error_code.message() << std::endl;
					}

					wait_for_client_connection();
				});
		}

		asio::ip::address get_local_ipv6_address()
		{
			asio::ip::tcp::resolver resolver(m_context);
			asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
			auto result = resolver.resolve(query);

			// My temporary ipv6 address happens to be the 5th entry of the query result
			// Do not use that on the production machine
			for (size_t i = 0; i < 4; i++)
				*result++;

			asio::ip::tcp::endpoint endpoint = *result;
			return endpoint.address();
		}

	private:
		asio::io_context m_context;
		std::thread m_context_thread;

		asio::ip::tcp::acceptor m_acceptor;

		tsqueue<Message<T>> m_message_queue;

		uint32_t m_id = 0;
	};
}

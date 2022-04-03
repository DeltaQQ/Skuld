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
			m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
		{}

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
				std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
				return false;
			}

			std::cout << "[SERVER] Started!" << std::endl;
			return true;
		}

		void stop()
		{
			m_context.stop();

			if (m_context_thread.joinable())
				m_context_thread.join();

			std::cout << "[SERVER] Stopped!" << std::endl;
		}

		void update()
		{
			m_message_queue.wait();
		}

	protected:
		virtual void on_message() {}

	private:
		void wait_for_client_connection()
		{
			m_acceptor.async_accept(
				[this](std::error_code error_code, asio::ip::tcp::socket socket)
				{
					if (!error_code)
					{
						std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << std::endl;
					}
					else
					{
						std::cout << "[SERVER] Connection Error: " << error_code.message() << std::endl;
					}

					wait_for_client_connection();
				});
		}

	private:
		asio::io_context m_context;
		std::thread m_context_thread;

		asio::ip::tcp::acceptor m_acceptor;

		tsqueue<Message<T>> m_message_queue;
	};
}

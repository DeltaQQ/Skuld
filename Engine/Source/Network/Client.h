#pragma once

#include <Data Structures/tsqueue.h>

#include "Common.h"
#include "Message.h"
#include "Connection.h"

namespace Net
{
	template <typename T>
	class Client
	{
	public:
		Client() = default;

		virtual ~Client()
		{
			disconnect();
		}

		void connect_to_server(const std::string& host, uint16_t port, const std::string& user_id)
		{
			try
			{
				asio::ip::tcp::resolver resolver(m_context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				m_connection = std::make_unique<Connection<T>>(
					Connection<T>::Owner::Client,
					asio::ip::tcp::socket(m_context),
					m_context,
					m_incoming_message_queue);

				m_connection->connect_to_server(endpoints);

				m_context_thread = std::thread([this]() { m_context.run(); });
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

		void disconnect()
		{
			if (is_connected()) m_connection->disconnect();

			m_context.stop();

			if (m_context_thread.joinable()) m_context_thread.join();

			m_connection.release();
		}

		bool is_connected() const
		{
			return m_connection ? m_connection->is_valid() : false;
		}

		void send(const Message<T>& message)
		{
			if (is_connected()) m_connection->send(message);
		}

	private:
		asio::io_context m_context;
		std::thread m_context_thread;

		std::unique_ptr<Connection<T>> m_connection;

		tsqueue<OwnedMessage<T>> m_incoming_message_queue;
	};
}
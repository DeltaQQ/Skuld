#pragma once

#include "Common.h"
#include "Message.h"
#include "Data Structures/tsqueue.h"

namespace Net
{
	template <typename T>
	class Server;

	template <typename T>
	class Connection : public std::enable_shared_from_this<Connection<T>>
	{
	public:
		enum class Owner
		{
			Client,
			Server
		};

	public:
		Connection(
			Owner owner, 
			asio::ip::tcp::socket socket, 
			asio::io_context& context, 
			tsqueue<OwnedMessage<T>>& incoming_message_queue)
			:
			m_owner(owner),
			m_socket(std::move(socket)),
			m_context(context),
			m_incoming_message_queue(incoming_message_queue)
		{}

		~Connection() = default;

		void connect_to_server(const asio::ip::tcp::resolver::results_type& endpoints)
		{
			if (m_owner == Owner::Client)
			{
				asio::async_connect(m_socket, endpoints,
					[this](std::error_code error_code, asio::ip::tcp::endpoint endpoint)
					{
						if (!error_code)
						{
							std::cout << "Connected!" << std::endl;
							read_header();
						}
						else
						{
							std::cout << error_code.message() << std::endl;
						}
					});
			}
		}

		void disconnect()
		{
			if (is_valid())
				asio::post(m_context, [this]() { m_socket.close(); });
		}

		bool is_valid() const
		{
			return m_socket.is_open();
		}

		void send(const Message<T>& message)
		{
			asio::post(m_context,
				[this, message]()
				{
					m_outgoing_message_queue.push_back(message);

					if (m_outgoing_message_queue.empty()) write_header();
				});
		}

		void read_header()
		{
			asio::async_read(m_socket, asio::buffer(&m_temporary_incoming_message.header, sizeof(MessageHeader<T>)),
				[this](std::error_code error_code, size_t length)
				{
					if (!error_code)
					{
						if (m_temporary_incoming_message.header.size > 0)
						{
							m_temporary_incoming_message.body.resize(m_temporary_incoming_message.header.size);
							read_body();
						}
						else
						{
							add_to_incoming_message_queue();
						}
					}
					else
					{
						std::cout << error_code.message() << std::endl;
						m_socket.close();
					}
				});
		}

		void read_body()
		{
			asio::async_read(m_socket, asio::buffer(m_temporary_incoming_message.body.data(), m_temporary_incoming_message.body.size()),
				[this](std::error_code error_code, size_t length)
				{
					if (!error_code)
					{
						add_to_incoming_message_queue();
					}
					else
					{
						std::cout << error_code.message() << std::endl;
						m_socket.close();
					}
				});
		}

		void write_header()
		{
			asio::async_write(m_socket, asio::buffer(&m_outgoing_message_queue.front().header, sizeof(MessageHeader<T>)), 
				[this](std::error_code error_code, size_t length)
				{
					if (!error_code)
					{
						if (m_outgoing_message_queue.front().body.size() > 0)
						{
							write_body();
						}
						else
						{
							m_outgoing_message_queue.pop_front();

							if (!m_outgoing_message_queue.empty())
							{
								write_header();
							}
						}
					}
					else
					{
						std::cout << error_code.message() << std::endl;
						m_socket.close();
					}
				});
		}

		void write_body()
		{
			asio::async_write(m_socket, asio::buffer(&m_outgoing_message_queue.front().header, sizeof(MessageHeader<T>)),
				[this](std::error_code error_code, size_t length)
				{
					if (!error_code)
					{
						m_outgoing_message_queue.pop_front();

						if (!m_outgoing_message_queue.empty())
						{
							write_header();
						}
					}
					else
					{
						std::cout << error_code.message() << std::endl;
						m_socket.close();
					}
				});
		}

		void add_to_incoming_message_queue()
		{
			if (m_owner == Owner::Server)
				m_incoming_message_queue.push_back({ this->shared_from_this(), m_temporary_incoming_message });
			else
				m_incoming_message_queue.push_back({ nullptr, m_temporary_incoming_message });

			read_header();
		}

	private:
		asio::ip::tcp::socket m_socket;

		asio::io_context& m_context;

		tsqueue<Message<T>> m_outgoing_message_queue;

		tsqueue<OwnedMessage<T>>& m_incoming_message_queue;

		Message<T> m_temporary_incoming_message;

		Owner m_owner;
	};
}
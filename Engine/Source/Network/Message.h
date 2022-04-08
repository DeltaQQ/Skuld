#pragma once
#include "Common.h"
#include <Data Structures/tsqueue.h>

namespace Net
{
	template <typename T>
	struct MessageHeader
	{
		T id = {};
		uint32_t size;
	};

	template <typename T>
	struct Message
	{
		MessageHeader<T> header = {};
		std::vector<uint8_t> body;

		size_t grab_index = 0;

		size_t size() const
		{
			return body.size();
		}

		friend std::ostream& operator << (std::ostream& ostream, const Message<T>& message)
		{
			ostream << "ID:" << int(message.header.id) << " Size:" << message.header.size;
			return ostream;
		}

		template <typename DataType>
		friend Message<T>& operator << (Message<T>& message, const DataType& data)
		{
			static_assert(std::is_trivially_copyable_v<DataType>, "DataType is not trivially copyable");

			size_t current_size = message.size();

			message.body.resize(current_size + sizeof(DataType));

			std::memcpy(message.body.data() + current_size, &data, sizeof(DataType));

			message.header.size = message.size();

			return message;
		}

		template <typename DataType>
		friend Message<T>& operator >> (Message<T>& message, const DataType& data)
		{
			if (message.grab_index >= message.size())
			{
				message.body.clear();
				return message;
			}

			static_assert(std::is_trivially_copyable_v<DataType>, "DataType is not trivially copyable");

			std::memcpy((void*)&data, message.body.data() + message.grab_index, sizeof(DataType));

			message.grab_index += sizeof(DataType);

			message.header.size = message.size() - sizeof(DataType);

			return message;
		}
	};

	template <typename T>
	class Connection;

	template <typename T>
	struct OwnedMessage
	{
		std::shared_ptr<Connection<T>> remote = nullptr;
		Message<T> message;

		friend std::ostream& operator<<(std::ostream& ostream, const OwnedMessage<T>& message)
		{
			ostream << message.message;
			return ostream;
		}
	};
}



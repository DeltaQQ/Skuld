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

	private:
		tsqueue<Message<T>> m_incoming_message_queue;
	};
}
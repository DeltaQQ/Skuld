#include <catch.hpp>

#include <Network/Message.h>

TEST_CASE("Stream various data in and out of a message")
{
	enum class MessageTypes : uint32_t
	{
		ClientAccepted,
		AddPlayer,
		RemovePlayer,
		UpdatePlayer
	};

	Net::Message<MessageTypes> message;
	message.header.id = MessageTypes::UpdatePlayer;

	REQUIRE(message.size() == 0);

	message << float(3.4) << double(5.6) << int(15) << false;
	
	REQUIRE(message.size() == 17);

	float a;
	double b;
	int c;
	bool d;

	message >> a >> b >> c >> d;

	REQUIRE(a == 3.4f);
	REQUIRE(b == 5.6);
	REQUIRE(c == 15);
	REQUIRE(!d);

	int i = 0;
	message >> i;

	REQUIRE(message.size() == 0);
}
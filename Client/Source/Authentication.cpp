#pragma once
#include "Authentication.h"

#include <iostream>
#include <fstream>
#include <json.hpp>

Authentication::Authentication()
	:
	m_app(nullptr),
	m_auth(nullptr)
{
	try
	{
		std::ifstream ifstream("firebase_config.json");
		nlohmann::json json;
		ifstream >> json;

		std::string api_key = json["apiKey"];
		std::string app_id = json["appId"];
		std::string messaging_sender_id = json["messagingSenderId"];
		std::string storage_bucket = json["storageBucket"];
		std::string project_id = json["projectId"];

		firebase::AppOptions options = {};
		options.set_api_key(api_key.c_str());
		options.set_app_id(app_id.c_str());
		options.set_messaging_sender_id(messaging_sender_id.c_str());
		options.set_storage_bucket(storage_bucket.c_str());
		options.set_project_id(project_id.c_str());

		m_app = firebase::App::Create(options);

		firebase::InitResult result;
		m_auth = firebase::auth::Auth::GetAuth(m_app, &result);
		m_auth->AddAuthStateListener(&m_auth_state_listener);

		if (result != firebase::kInitResultSuccess)
		{
			std::stringstream error_message;
			error_message << "Failed to create firebase::auth:Auth Object" << std::endl;
			throw std::exception(error_message.str().c_str());
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool Authentication::sign_in(const std::string& email, const std::string& password)
{
	auto result = m_auth->SignInWithEmailAndPassword(email.c_str(), password.c_str());

	while (result.status() != firebase::kFutureStatusComplete);

	if (result.error() != firebase::auth::kAuthErrorNone)
	{
		std::cout << result.error_message() << std::endl;
		return false;
	}

	std::cout << "Successfully logged in" << std::endl;

	return true;
}

void Authentication::sign_out()
{
	m_auth->SignOut();
}

bool Authentication::is_signed_in()
{
	if (m_auth->current_user())
		return true;

	return false;
}

bool Authentication::is_verified()
{
	auto user = m_auth->current_user();

	return user && user->is_email_verified() ? true : false;
}

std::string Authentication::get_user_id()
{
	std::string user_id = m_auth->current_user()->uid();

	return user_id;
}

Authentication::~Authentication()
{
	if (is_signed_in())
		sign_out();

	m_auth->RemoveAuthStateListener(&m_auth_state_listener);

	// Possible memory leak if firebase doesn't do any cleanup under the hood
	m_auth = nullptr;
	m_app = nullptr;
}

void AuthStateListener::OnAuthStateChanged(firebase::auth::Auth* auth)
{
	auto user = auth->current_user();
}

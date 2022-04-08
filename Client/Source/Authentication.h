#pragma once

#include <firebase/app.h>
#include <firebase/auth.h>

class AuthStateListener : public firebase::auth::AuthStateListener
{
public:
	void OnAuthStateChanged(firebase::auth::Auth* auth) override;
};

class Authentication
{
public:
	Authentication();
	~Authentication();

	bool sign_in(const std::string& email, const std::string& password);
	void sign_out();

	bool is_signed_in();
	bool is_verified();

	std::string get_user_id();

private:
	firebase::App* m_app;
	firebase::auth::Auth* m_auth;

	AuthStateListener m_auth_state_listener;
};

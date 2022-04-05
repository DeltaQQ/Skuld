#include <pqxx/pqxx>

class Database
{
public:
	Database();
	~Database();

private:
	pqxx::connection* m_connection;
};
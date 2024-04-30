#include "DbConnector.h"

DbConnector::DbConnector()
{
	connection = gcnew MySqlConnection("server=localhost;" +
		"port=3306;" +
		"username=root;" +
		"password=;" +
		"database=(311)database;" +
		"SslMode=none");
}

void DbConnector::OpenConnection()
{
	// Проверяем состояние подключения
	if (connection->State == System::Data::ConnectionState::Closed)
		connection->Open();
}

void DbConnector::CloseConnection()
{
	// Проверяем, есть ли соеденение 
	if (connection->State == System::Data::ConnectionState::Open)
		connection->Close();
}

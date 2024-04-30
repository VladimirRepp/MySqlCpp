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
	// ��������� ��������� �����������
	if (connection->State == System::Data::ConnectionState::Closed)
		connection->Open();
}

void DbConnector::CloseConnection()
{
	// ���������, ���� �� ���������� 
	if (connection->State == System::Data::ConnectionState::Open)
		connection->Close();
}

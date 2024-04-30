#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Data::OleDb;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

/*
* ������:
    Connector MySQL: https://dev.mysql.com/downloads/connector/cpp/
    MySQL ZIP Archive: https://dev.mysql.com/downloads/mysql/

* �����:
    Debug \\ MySql.Data.dll
    Debug \\ MySql.Data.xml

    Root \\ libmysql.lib
*/


ref class DbConnector
{
private:
    // C������ ���� ������ ���������� � MySql
    MySqlConnection^ connection;
    
public:
    DbConnector();

    // ������� ����������
    property MySqlConnection^ Connection {
        MySqlConnection^ get() {
            return connection;
        }
    }

    void OpenConnection();              // ������� ���������� � ��������
    void CloseConnection();             // ������� ���������� � ��������
};


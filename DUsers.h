#pragma once

#include "DatabaseManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data::SqlClient;

// ������ ������������
// ref => ����������� �����
ref class User {
public:
	int Id;
	String^ Login;
	String^ Password;
	String^ Fullname;
	String^ Status;

	User() {}
	User(int Id, String^ Login, String^ Password, String^ Fullname, String^ Status) : 
		Id(Id), Login(Login), Password(Password), Fullname(Fullname), Status(Status) {}
};

// ����� ��� ������ � ������������ �������������
ref class DUsers
{
	// ���� ������
private: // �������� �����
	static User^ _selectedUser;
	List<User^>^ _data;
	String^ _tableName;
	DatabaseManager^ _dbManager;

	// ������ ������
public: // �������� �����
	DUsers();

	int Count();
	List<User^>^ Data();
	User^ GetSelectedUser();
	void SetSelectedUser(User^ d);
	bool Query_SelectAll();
	bool Query_Insert(User^ d);
	bool Query_Update(User^ d);
	bool Query_Delete(int id);
	bool Query_Authorization(String^ login, String^ password);
	bool Query_HasLogin(String^ login);

	User^ operator[](int index);
};


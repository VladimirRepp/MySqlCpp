#pragma once

#include "DatabaseManager.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Data::SqlClient;

// Данные пользователя
// ref => управляемый класс
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

// Класс для работы с функционалом пользователей
ref class DUsers
{
	// Поля класса
private: // закрытая часть
	static User^ _selectedUser;
	List<User^>^ _data;
	String^ _tableName;
	DatabaseManager^ _dbManager;

	// Методы класса
public: // открытая часть
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


#include "DUsers.h"

DUsers::DUsers()
{
    _selectedUser = nullptr;
    _data = gcnew List<User^>();
    _dbManager = gcnew DatabaseManager();
    _tableName = "users";
}

int DUsers::Count()
{
    return _data->Count;
}

List<User^>^ DUsers::Data()
{
    return _data;
}

User^ DUsers::GetSelectedUser()
{
    return _selectedUser;
}

void DUsers::SetSelectedUser(User^ d)
{
    _selectedUser = d;
}

bool DUsers::Query_SelectAll()
{
    bool done = false;

    MySqlCommand^ command = gcnew MySqlCommand("SELECT * FROM  `" + _tableName + "`", _dbManager->GetConnection());
    MySqlDataReader^ reader;

    try {
        _dbManager->OpenConnection();     
        reader = command->ExecuteReader();

        if (reader->HasRows) 
        {
            _data->Clear();
            done = true;

            while (reader->Read())
            {
                _data->Add(gcnew User(Convert::ToInt32(reader["Id"]), 
                    reader["login"]->ToString(), reader["password"]->ToString(),
                    reader["fullname"]->ToString(), reader["status"]->ToString()));
            }
        }
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return done;
}

bool DUsers::Query_Insert(User^ d)
{
    bool done = false;
    MySqlCommand^ command = gcnew MySqlCommand("INSERT INTO `" + _tableName + "` (`id`, `login`, `password`, `fullname`, `status`) VALUES " +
        "(NULL, '" + d->Login + "', '" + d->Password + "', '" + d->Fullname + "', '" + d->Status + "')", _dbManager->GetConnection());

    try {
        _dbManager->OpenConnection();
        command->ExecuteNonQuery();
        _data->Add(d);
        done = true;
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return done;
}

bool DUsers::Query_Update(User^ d)
{
    bool done = false;
    MySqlCommand^ command = gcnew MySqlCommand("UPDATE `" + _tableName + "` SET login = '" + d->Login + "', password = '" + d->Password + "', fullname = '" + d->Fullname + "', status = '" + d->Status + "' WHERE id = " + d->Id, 
        _dbManager->GetConnection());

    try {
        _dbManager->OpenConnection();
        command->ExecuteNonQuery();
        
        for (int i = 0; i < _data->Count; i++) {
            if (d->Id == _data[i]->Id) {
                _data[i] = d;
                done = true;
                break;
            }
        }        
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return done;
}

bool DUsers::Query_Delete(int id)
{
    bool done = false;
    MySqlCommand^ command = gcnew MySqlCommand("DELETE FROM `" + _tableName + "` WHERE id = " + id,
        _dbManager->GetConnection());

    try {
        _dbManager->OpenConnection();
        command->ExecuteNonQuery();

        for (int i = 0; i < _data->Count; i++) {
            if (id == _data[i]->Id) {
                done = true;
                _data->RemoveAt(i);
                break;
            }
        }       
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return done;
}

bool DUsers::Query_Authorization(String^ login, String^ password)
{
    bool done = false;

    MySqlCommand^ command = gcnew MySqlCommand("SELECT * FROM `" + _tableName + "` WHERE login = '" + login + "' AND password = '" + password + "'", _dbManager->GetConnection());
    MySqlDataReader^ reader;

    try {
        _dbManager->OpenConnection();
        reader = command->ExecuteReader();

        if (reader->HasRows)
        {
            done = true;

            while (reader->Read())
            {
                _selectedUser =  gcnew User(Convert::ToInt32(reader["id"]),
                    reader["login"]->ToString(), reader["password"]->ToString(),
                    reader["fullname"]->ToString(), reader["status"]->ToString());
            }
        }
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return done;
}

bool DUsers::Query_HasLogin(String^ login)
{
    bool has = false;

    MySqlCommand^ command = gcnew MySqlCommand("SELECT * FROM `" + _tableName + "` WHERE login = '" + login + "'", _dbManager->GetConnection());
    MySqlDataReader^ reader;

    try {
        _dbManager->OpenConnection();
        reader = command->ExecuteReader();

        if (reader->HasRows)
        {
            has = true;
        }
    }
    catch (Exception^ ex) {
        throw ex;
    }
    finally {
        _dbManager->CloseConnection();
    }

    return has;
}

User^ DUsers::operator[](int index)
{
    if (index < 0 || index >= _data->Count) {
        throw gcnew Exception("Индекс вне диапазона!");
    }

    return _data[index];
}

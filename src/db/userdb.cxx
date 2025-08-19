#include "db/userdb.hxx"
#include "types/serverexception.hxx"

#include <sqlite3.h>

DB::UserDB* DB::UserDB::m_instance = nullptr;

DB::UserDB::UserDB()
    : DB::SQLite(DB_TABLE_USERS)
{
    std::vector<std::string> columns = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "username TEXT UNIQUE NOT NULL CHECK(length(username) >= 3)",
        "password TEXT NOT NULL",
    };
    createTable(columns);
}

DB::UserDB* DB::UserDB::GetDatabase()
{
    if ( nullptr == m_instance )
    {
        m_instance = new DB::UserDB();
    }
    return m_instance;
}

void DB::UserDB::AddUser(const User& user)
{
    try
    {
        Insert("username, password", {user.GetUsername(), user.GetPassword()});
    }
    catch (const ServerException& e)
    {
        if ( DB_UNIQUE_ERROR == e.code() )
        {
            throw ServerException(DB_UNIQUE_UNAME_ERROR);
        }
        throw e;
    }
}

void DB::UserDB::IsUserExists(const User& user)
{
    std::map<int, std::string> values = {{1, ""}, {2, ""}};
    std::map<std::string, std::string> stmtMap = {
        {"username", user.GetUsername()}
    };
    try
    {
        Select(values, "*", stmtMap, 1);
    }
    catch (const ServerException& e)
    {
        if ( DB_VALUE_NOT_FOUND == e.code() )
        {
            throw ServerException(DB_USER_NOT_FOUND);
        }
        throw e;
    }
    if ( user.GetPassword() != values[2] )
    {
        throw ServerException(DB_PASSWORD_IS_INCORRECT);
    }
}

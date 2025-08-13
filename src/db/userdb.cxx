#include "db/userdb.hxx"

#include <iostream>
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

bool DB::UserDB::AddUser(const User& user)
{
    Insert("username, password", {user.GetUsername(), user.GetPassword()});
    return true;
}

bool DB::UserDB::GetByUsername(const std::string& username, User& user)
{
    std::string sql = "SELECT * FROM ";
    sql += DB_TABLE_USERS;
    sql += " WHERE username=? LIMIT 1;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        return false;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if ( SQLITE_ROW != sqlite3_step(stmt) )
    {
        sqlite3_finalize(stmt);
        return false;
    }
    User foundUser( (char*)sqlite3_column_text(stmt, 1),
            (char*)sqlite3_column_text(stmt, 2));
    user = foundUser;
    sqlite3_finalize(stmt);
    return true;
}

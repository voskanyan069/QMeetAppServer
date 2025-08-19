#ifndef __DB_USER_DB_HXX__
#define __DB_USER_DB_HXX__

#define DB_TABLE_USERS  "users"

#include "db/sqlite.hxx"
#include "types/user.hxx"

namespace DB
{
    class UserDB;
}

class DB::UserDB final : public DB::SQLite
{
private:
    UserDB();

public:
    ~UserDB() = default;
    UserDB(const UserDB&) = delete;
    UserDB& operator=(const UserDB&) = delete;

public:
    static UserDB* GetDatabase();

public:
    void AddUser(const User& user);
    void IsUserExists(const User& user);

private:
    static UserDB* m_instance;
};

#endif // !__DB_USER_DB_HXX__

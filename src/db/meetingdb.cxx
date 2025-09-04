#include "db/meetingdb.hxx"
#include "types/serverexception.hxx"

#include <sqlite3.h>

DB::MeetingDB* DB::MeetingDB::m_instance = nullptr;

DB::MeetingDB::MeetingDB()
    : DB::SQLite(DB_TABLE_MEETINGS)
{
    std::vector<std::string> columns = {
        "id INTEGER PRIMARY KEY AUTOINCREMENT",
        "meet_id TEXT UNIQUE NOT NULL CHECK(length(meet_id) >= 3)",
        "password TEXT NOT NULL",
    };
    createTable(columns);
}

DB::MeetingDB* DB::MeetingDB::GetDatabase()
{
    if ( nullptr == m_instance )
    {
        m_instance = new DB::MeetingDB();
    }
    return m_instance;
}

void DB::MeetingDB::AddMeeting(const Meeting& info)
{
    try
    {
        Insert("meet_id, password", {info.GetID(), info.GetPassword()});
    }
    catch (const ServerException& e)
    {
        if ( DB_UNIQUE_ERROR == e.code() )
        {
            throw ServerException(DB_UNIQUE_MEET_ERROR);
        }
        throw e;
    }
}

void DB::MeetingDB::IsMeetingExists(const Meeting& info)
{
    std::map<int, std::string> values = {{1, ""}, {2, ""}};
    std::map<std::string, std::string> stmtMap = {
        {"meet_id", info.GetID()}
    };
    try
    {
        Select(values, "*", stmtMap, 1);
    }
    catch (const ServerException& e)
    {
        if ( DB_VALUE_NOT_FOUND == e.code() )
        {
            throw ServerException(DB_MEETING_NOT_FOUND);
        }
        throw e;
    }
    if ( info.GetPassword() != values[2] )
    {
        throw ServerException(DB_PASSWORD_IS_INCORRECT);
    }
}

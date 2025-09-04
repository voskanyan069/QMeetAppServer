#ifndef __DB_MEETING_DB_HXX__
#define __DB_MEETING_DB_HXX__

#define DB_TABLE_MEETINGS   "meetings"

#include "db/sqlite.hxx"
#include "types/meeting.hxx"

namespace DB
{
    class MeetingDB;
}

class DB::MeetingDB final : public DB::SQLite
{
private:
    MeetingDB();

public:
    ~MeetingDB() = default;
    MeetingDB(const MeetingDB&) = delete;
    MeetingDB& operator=(const MeetingDB&) = delete;

public:
    static MeetingDB* GetDatabase();

public:
    void AddMeeting(const Meeting& user);
    void IsMeetingExists(const Meeting& user);

private:
    static MeetingDB* m_instance;
};

#endif // !__DB_MEETING_DB_HXX__

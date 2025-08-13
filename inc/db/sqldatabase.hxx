#ifndef __DB_SQLDATABASE_HXX__
#define __DB_SQLDATABASE_HXX__

#define DBFILENAME  "database.db"

#include <string>
#include <vector>
#include <map>

namespace DB
{
    class SQLDatabase;
}

class DB::SQLDatabase
{
public:
    virtual ~SQLDatabase() = default;

public:
    virtual void Insert(const std::string& valOrder,
            const std::vector<std::string>& values) = 0;
    virtual void Update(const std::map<std::string, std::string>& updateSql,
            const std::string& stmt) = 0;
    virtual void Remove(const std::string& stmt) = 0;

protected:
    virtual void initalize() = 0;
    virtual void finalize() = 0;
    virtual void createTable(const std::vector<std::string>& columns) = 0;
    virtual void execute(const std::string& sql) = 0;
};

#endif // ! __DB_SQLDATABASE_HXX__

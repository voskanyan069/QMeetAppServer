#ifndef __DB_SQLITE_HXX__
#define __DB_SQLITE_HXX__

#include "db/sqldatabase.hxx"
#include <string>

class sqlite3;
namespace DB
{
    class SQLite;
}

class DB::SQLite : public DB::SQLDatabase
{
public:
    SQLite(const std::string& tableName);
    virtual ~SQLite();

public:
    virtual void Insert(const std::string& valOrder,
            const std::vector<std::string>& values) override;
    virtual void Update( const std::map<std::string, std::string>& updateSql,
            const std::string& stmt) override;
    virtual void Remove(const std::string& stmt) override;
    virtual void Select(std::map<int, std::string>& values,
            const std::string& cols = "*",
            const std::map<std::string, std::string>& stmtMap = {},
            unsigned int limit = 0) override;

protected:
    virtual void initalize() override;
    virtual void finalize() override;
    virtual void createTable(const std::vector<std::string>& columns) override;
    virtual void execute(const std::string& sql) override;

protected:
    static sqlite3* PTR_DB;
    std::string m_tableName;

private:
    static bool IsOpen;
};

#endif // ! __DB_SQLITE_HXX__

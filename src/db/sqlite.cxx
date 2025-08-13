#include "db/sqlite.hxx"

#include <sqlite3.h>
#include <iostream>

DB::SQLite::SQLite(const std::string& table)
    : m_db(nullptr)
    , m_tableName(table)
{
    initalize();
}

DB::SQLite::~SQLite()
{
    finalize();
}

void DB::SQLite::Insert(const std::string& valOrder,
        const std::vector<std::string>& values)
{
    if ( 0 == values.size() )
    {
        return;
    }
    std::string sql = "INSERT INTO " + m_tableName + " (" +
        valOrder + ") VALUES (";
    int i = 0;
    for (; i < values.size() - 1; ++i)
    {
        sql += "'" + values[i] + "', ";
    }
    sql += "'" + values[i] + "');";
    execute(sql);
}

void DB::SQLite::Update(
        const std::map<std::string, std::string>& updateSql,
        const std::string& stmt)
{
    std::string sqlStmt = "";
    if ( updateSql.empty() )
    {
        return;
    }
    if ( !stmt.empty() )
    {
        sqlStmt = " WHERE " + stmt;
    }
    std::string sql = "UPDATE " + m_tableName + " SET ";
    auto it = updateSql.begin();
    for (; it != std::prev(updateSql.end()); ++it)
    {
        sql += it->first + " = '" + it->second + "', ";
    }
    sql += it->first + " = '" + it->second + "' " + sqlStmt + ";";
    execute(sql);
}

void DB::SQLite::Remove(const std::string& stmt)
{
    if ( stmt.empty() )
    {
        return;
    }
    std::string sql = "DELETE FROM " + m_tableName + " WHERE " + stmt + ";";
    execute(sql);
}

void DB::SQLite::initalize()
{
    int rc = sqlite3_open(DBFILENAME, &m_db);
    if ( SQLITE_OK != rc )
    {
        finalize();
    }
}

void DB::SQLite::finalize()
{
    if ( nullptr == m_db )
    {
        return;
    }
    sqlite3_close(m_db);
    m_db = nullptr;
}

void DB::SQLite::createTable(const std::vector<std::string>& columns)
{
    if ( 0 == columns.size() )
    {
        return;
    }
    std::string sql = "CREATE TABLE IF NOT EXISTS " + m_tableName + "(";
    int i = 0;
    for ( ; i < columns.size() - 1; ++i )
    {
        sql += columns[i] + ",";
    }
    sql += columns[i] + ");";
    execute(sql);
}

void DB::SQLite::execute(const std::string& sql)
{
    std::cout << "Execute SQL: " << sql << std::endl;
    char* errMsg = nullptr;
    int rc = sqlite3_exec(m_db, sql.c_str(), nullptr, nullptr, &errMsg);
    if ( SQLITE_OK != rc )
    {
        std::cout << "SQL command failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

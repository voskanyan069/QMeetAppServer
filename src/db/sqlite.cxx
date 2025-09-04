#include "db/sqlite.hxx"
#include "types/serverexception.hxx"

#include <sqlite3.h>

#include <iostream>

sqlite3* DB::SQLite::PTR_DB = nullptr;
bool DB::SQLite::IsOpen = false;

DB::SQLite::SQLite(const std::string& table)
    : m_tableName(table)
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
        throw ServerException("Insertation values list cannot be empty");
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

void DB::SQLite::Select(std::map<int, std::string>& values,
        const std::string& cols,
        const std::map<std::string, std::string>& stmtMap,
        unsigned int limit)
{
    std::string sqlOpt = "";
    std::vector<std::string> condValues;
    if ( !stmtMap.empty() )
    {
        sqlOpt += " WHERE ";
        if ( 1 == stmtMap.size() )
        {
            auto it = stmtMap.begin();
            sqlOpt += it->first + "=?";
            condValues.push_back(it->second);
        }
        else
        {
            auto it = stmtMap.begin();
            for (; it != std::prev(stmtMap.end()); ++it)
            {
                sqlOpt += it->first + "=? AND ";
                condValues.push_back(it->second);
            }
            sqlOpt += it->first + "=?";
            condValues.push_back(it->second);
        }
    }
    if ( 0 != limit )
    {
        sqlOpt += " LIMIT " + std::to_string(limit);
    }
    std::string sql = "SELECT " + cols + " FROM " + m_tableName + sqlOpt + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(PTR_DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        throw ServerException(DB_FAILED_TO_SEARCH);
    }
    for (int i = 1; i < condValues.size()+1; ++i)
    {
        sqlite3_bind_text(stmt, i, condValues[i-1].c_str(), -1, SQLITE_STATIC);
    }
    rc = sqlite3_step(stmt);
    if ( rc != SQLITE_ROW )
    {
        sqlite3_finalize(stmt);
        throw ServerException(DB_VALUE_NOT_FOUND);
    }
    for ( auto& it : values )
    {
        it.second = (const char*)sqlite3_column_text(stmt, it.first);
    }
}

void DB::SQLite::initalize()
{
    if (IsOpen)
    {
        return;
    }
    IsOpen = true;
    int rc = sqlite3_open(DBFILENAME, &PTR_DB);
    if ( SQLITE_OK != rc )
    {
        finalize();
    }
}

void DB::SQLite::finalize()
{
    if ( nullptr == PTR_DB )
    {
        return;
    }
    IsOpen = false;
    sqlite3_close(PTR_DB);
    PTR_DB = nullptr;
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
    char* errMsg = nullptr;
    int rc = sqlite3_exec(PTR_DB, sql.c_str(), nullptr, nullptr, &errMsg);
    std::string sError;
    if ( nullptr != errMsg )
    {
        sError = errMsg;
    }
    sqlite3_free(errMsg);
    if ( SQLITE_OK != rc )
    {
        if ( std::string::npos != sError.find("UNIQUE constraint failed") )
        {
            throw ServerException(DB_UNIQUE_ERROR);
        }
        throw ServerException(sError);
    }
}

#ifndef __TYPES_SERVER_EXCEPTION_HXX__
#define __TYPES_SERVER_EXCEPTION_HXX__

#include <exception>
#include <string>
#include <map>

#define DB_UNIQUE_ERROR             1000
#define DB_UNIQUE_UNAME_ERROR       1001
#define DB_UNIQUE_MEET_ERROR        1002
#define DB_FAILED_TO_SEARCH         2000
#define DB_VALUE_NOT_FOUND          2001
#define DB_USER_NOT_FOUND           2002
#define DB_MEETING_NOT_FOUND        2003
#define DB_PASSWORD_IS_INCORRECT    3000

const static std::map<int, std::string> ERROR_LIST = {
    {DB_UNIQUE_ERROR, "The specified value is not unique"},
    {DB_UNIQUE_UNAME_ERROR, "The user with this username already exists"},
    {DB_FAILED_TO_SEARCH, "Failed to search requested data"},
    {DB_VALUE_NOT_FOUND, "The requested data does not found"},
    {DB_USER_NOT_FOUND, "The user with this username does not found"},
    {DB_PASSWORD_IS_INCORRECT, "The password is incorrect"},
    {DB_UNIQUE_MEET_ERROR, "The meeting with this name already exists"},
    {DB_MEETING_NOT_FOUND, "The meeting with this name does not found"}
};

class ServerException : public std::exception
{
public:
    explicit ServerException(const std::string& msg, int iCode = -1)
        : message(msg)
        , m_code(iCode)
    {
    }

    explicit ServerException(int iCode)
        : message()
        , m_code(iCode)
    {
        auto it = ERROR_LIST.find(iCode);
        if ( ERROR_LIST.end() != it )
        {
            message = it->second;
        }
    }

    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }

    virtual int code() const noexcept
    {
        return m_code;
    }

private:
    std::string message;
    int m_code;
};

#endif // ! __TYPES_SERVER_EXCEPTION_HXX__

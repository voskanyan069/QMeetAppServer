#ifndef __SERVER_RESTAPI_HXX__
#define __SERVER_RESTAPI_HXX__

#define USERS_DATABASE  "users.db"

#include "server/server.hxx"
#include "db/userdb.hxx"
#include "db/meetingdb.hxx"

#include "crow.h"

namespace Server
{
    class RestAPI;
}

class Server::RestAPI : public Server::Server
{
public:
    RestAPI();
    ~RestAPI();

public:
    virtual void Init(const Configs&) override;
    virtual void Run() override;

private:
    void defineCreateAccountRoute();
    void defineGetAccountRoute();
    void defineCreateMeetingRoute();
    void defineGetMeetingRoute();
    void defineRoutes();
    void callRouteFunction(const std::string& sFuncName);

private:
    int m_port;
    crow::SimpleApp m_crow;
    DB::UserDB* m_userDB;
    DB::MeetingDB* m_meetingDB;
};

#endif // ! __SERVER_RESTAPI_HXX__

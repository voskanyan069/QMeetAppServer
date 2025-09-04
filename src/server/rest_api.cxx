#include "server/rest_api.hxx"
#include "server/rest/routes.hxx"
#include "types/serverexception.hxx"
#include "types/user.hxx"
#include "types/meeting.hxx"

Server::RestAPI::RestAPI()
    : m_port(55005)
    , m_crow()
    , m_userDB(DB::UserDB::GetDatabase())
    , m_meetingDB(DB::MeetingDB::GetDatabase())
{
}

Server::RestAPI::~RestAPI()
{
}

void Server::RestAPI::Init(const Configs& configs)
{
    Config<int> port(configs.GetConfigPtr<int>("port"));
    if (port)
    {
        port.Write(m_port);
    }
    defineRoutes();
}

void Server::RestAPI::Run()
{
    m_crow
        .port(m_port)
        .multithreaded()
        .run();
}

void Server::RestAPI::defineCreateAccountRoute()
{
    CROW_ROUTE(m_crow, ROUTE_CREATE_ACCOUNT) ([this](const crow::request& req)
    {
        std::string uname = req.url_params.get("username");
        std::string passwd = req.url_params.get("password");
        crow::json::wvalue resp;
        try
        {
            m_userDB->AddUser(User(uname, passwd));
            resp["error"] = "ok";
        }
        catch (const ServerException& e)
        {
            resp["error"] = e.what();
            resp["code"] = e.code();
        }
        return resp;
    });
}

void Server::RestAPI::defineGetAccountRoute()
{
    CROW_ROUTE(m_crow, ROUTE_CHECK_USER_EXISTS)([this](const crow::request& req)
    {
        std::string uname = req.url_params.get("username");
        std::string passwd = req.url_params.get("password");
        crow::json::wvalue resp;
        try
        {
            m_userDB->IsUserExists(User(uname, passwd));
            resp["exists"] = true;
            resp["error"] = "ok";
        }
        catch (const ServerException& e)
        {
            resp["error"] = e.what();
            resp["code"] = e.code();
        }
        return resp;
    });
}

void Server::RestAPI::defineCreateMeetingRoute()
{
    CROW_ROUTE(m_crow, ROUTE_CREATE_MEETING)([this](const crow::request& req)
    {
        std::string id = req.url_params.get("id");
        std::string passwd = req.url_params.get("password");
        crow::json::wvalue resp;
        try
        {
            m_meetingDB->AddMeeting(Meeting(id, passwd));
            resp["error"] = "ok";
        }
        catch (const ServerException& e)
        {
            resp["error"] = e.what();
            resp["code"] = e.code();
        }
        return resp;
    });
}

void Server::RestAPI::defineGetMeetingRoute()
{
    CROW_ROUTE(m_crow, ROUTE_CHECK_MEET_EXISTS)([this](const crow::request& req)
    {
        std::string id = req.url_params.get("id");
        std::string passwd = req.url_params.get("password");
        crow::json::wvalue resp;
        try
        {
            m_meetingDB->IsMeetingExists(Meeting(id, passwd));
            resp["exists"] = "ok";
            resp["error"] = "ok";
        }
        catch (const ServerException& e)
        {
            resp["error"] = e.what();
            resp["code"] = e.code();
        }
        return resp;
    });
}

void Server::RestAPI::defineRoutes()
{
    defineCreateAccountRoute();
    defineGetAccountRoute();
    defineCreateMeetingRoute();
    defineGetMeetingRoute();
}

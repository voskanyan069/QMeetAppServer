#include "server/rest_api.hxx"
#include "server/rest/routes.hxx"
#include "db/userdb.hxx"

#include <crow.h>

#include <iostream>

Server::RestAPI::RestAPI()
    : m_crow()
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
    std::cout << "Run REST-API server: " << m_port << std::endl;
    m_crow
        .port(m_port)
        .multithreaded()
        .run();
}

void Server::RestAPI::defineRoutes()
{
    CROW_ROUTE(m_crow, ROUTE_SIGNIN) ([](const crow::request& req)
            {
                std::string uname = req.url_params.get("username");
                std::string passwd = req.url_params.get("password");
                crow::json::wvalue resp;
                resp["username"] = uname;
                resp["password"] = passwd;
                DB::UserDB* db = DB::UserDB::GetDatabase();
                db->AddUser(User(uname, passwd));
                User u(uname, passwd);
                if ( !db->GetByUsername("andrank", u) )
                {
                    std::cout << "User not found" << std::endl;
                    return resp;
                }
                std::cout << "u: " << u.GetUsername() << ":"
                    << u.GetPassword() << std::endl;
                return resp;
            });
}

#include "server/rest_api.hxx"
#include "types/configs.hxx"

#include <iostream>

int main()
{
    Server::Server* pServer = new Server::RestAPI();
    Configs configs;
    configs.Insert("port", 55005);
    pServer->Init(configs);
    pServer->Run();
    delete pServer;
    return 0;
}

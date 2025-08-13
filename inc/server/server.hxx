#ifndef __SERVER_SERVER_HXX__
#define __SERVER_SERVER_HXX__

#include "types/configs.hxx"

namespace Server
{
    class Server;
}

class Server::Server
{
public:
    virtual void Init(const Configs&) = 0;
    virtual void Run() = 0;
};

#endif // ! __SERVER_SERVER_HXX__

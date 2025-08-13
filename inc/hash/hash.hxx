#ifndef __HASH_HASHBASE_HXX__
#define __HASH_HASHBASE_HXX__

#include <string>

namespace Hash
{
    class HashBase;
}

class Hash::HashBase
{
public:
    virtual ~HashBase() = default;

public:
    virtual void Hash(const std::string& src, std::string& result) = 0;
};

#endif // ! __HASH_HASHBASE_HXX__

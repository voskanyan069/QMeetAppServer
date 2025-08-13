#ifndef __TYPES_USER_HXX__
#define __TYPES_USER_HXX__

#include "hash/sha256.hxx"
#include <string>

class User
{
public:
    explicit User(const std::string& username, const std::string& password,
            Hash::HashBase* hasher = Hash::SHA256::GetInstance());
    ~User() = default;

public:
    std::string GetUsername() const;
    std::string GetPassword() const;

private:
    void hash(Hash::HashBase*, const std::string& src, std::string& result);

private:
    std::string m_username;
    std::string m_password;
};

#endif // ! __TYPES_USER_HXX__

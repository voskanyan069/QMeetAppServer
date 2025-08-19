#include "types/user.hxx"
#include "hash/hash.hxx"

User::User()
    : m_username()
    , m_password()
{
}

User::User(const std::string& username, const std::string& password,
        Hash::HashBase* hasher)
    : m_username()
    , m_password()
{
    hash(hasher, username, m_username);
    hash(hasher, password, m_password);
}

std::string User::GetUsername() const
{
    return m_username;
}

std::string User::GetPassword() const
{
    return m_password;
}

void User::hash(Hash::HashBase* hasher, const std::string& src,
        std::string& result)
{
    hasher->Hash(src, result);
}

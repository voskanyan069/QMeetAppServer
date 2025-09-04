#include "types/meeting.hxx"
#include "hash/hash.hxx"

Meeting::Meeting()
    : m_id()
    , m_password()
{
}

Meeting::Meeting(const std::string& id, const std::string& password,
        Hash::HashBase* hasher)
    : m_id()
    , m_password()
{
    hash(hasher, id, m_id);
    hash(hasher, password, m_password);
}

std::string Meeting::GetID() const
{
    return m_id;
}

std::string Meeting::GetPassword() const
{
    return m_password;
}

void Meeting::hash(Hash::HashBase* hasher, const std::string& src,
        std::string& result)
{
    hasher->Hash(src, result);
}

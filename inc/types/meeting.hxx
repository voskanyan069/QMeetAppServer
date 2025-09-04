#ifndef __TYPES_MEETING_HXX__
#define __TYPES_MEETING_HXX__

#include "hash/sha256.hxx"
#include <string>

class Meeting
{
public:
    Meeting();
    explicit Meeting(const std::string& id, const std::string& password,
            Hash::HashBase* hasher = Hash::SHA256::GetInstance());
    ~Meeting() = default;

public:
    std::string GetID() const;
    std::string GetPassword() const;

private:
    void hash(Hash::HashBase*, const std::string& src, std::string& result);

private:
    std::string m_id;
    std::string m_password;
};

#endif // ! __TYPES_MEETING_HXX__

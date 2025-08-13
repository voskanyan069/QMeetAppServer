#include "types/configs.hxx"

Configs::Configs()
    : m_configs()
{
}

Configs::~Configs()
{
    for (auto& cnf : m_configs)
    {
        delete cnf.second;
    }
    m_configs.clear();
}

void Configs::Remove(const std::string& key)
{
    auto it = m_configs.find(key);
    if ( m_configs.end() == it )
    {
        return;
    }
    if ( nullptr != it->second )
    {
        delete it->second;
    }
    m_configs.erase(it);
}

void Configs::GetConfigs(ConfigsMap& map) const
{
    map = m_configs;
}

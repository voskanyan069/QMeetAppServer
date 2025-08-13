#ifndef __TYPES_CONFIGS_HXX__
#define __TYPES_CONFIGS_HXX__

#include <map>
#include <string>
#include <memory>

template <typename T>
struct Config;
class Configs;
class ConfigArgument;
template <typename T>
class ConfigArgumentImpl;
typedef std::map<std::string, ConfigArgument*> ConfigsMap;

template <typename T>
struct Config
{
    bool found = false;
    T* data = nullptr;

    operator bool()
    {
        return found;
    }

    void Write(T& var)
    {
        var = *data;
    }
};

class ConfigArgument
{
public:
    virtual ~ConfigArgument() = default;

public:
    template <typename T>
    T* GetPtr()
    {
        ConfigArgumentImpl<T>* impl = dynamic_cast<ConfigArgumentImpl<T>*>
            (this);
        return impl->GetPtr();
    }
};

template <typename T>
class ConfigArgumentImpl : public ConfigArgument
{
public:
    ConfigArgumentImpl(std::shared_ptr<T> ptr)
        : m_data(std::move(ptr))
    {
    }

    ConfigArgumentImpl(const T& data)
        : m_data(std::make_shared<T>(data))
    {
    }

    T* GetPtr() const
    {
        return m_data.get();
    }

private:
    std::shared_ptr<T> m_data;
};

class Configs
{
public:
    Configs();
    ~Configs();

public:
    template <typename T>
    void Insert(const std::string& key, const T& val)
    {
        m_configs[key] = new ConfigArgumentImpl<T>(val);
    }

    template <typename T>
    Config<T> GetConfigPtr(const std::string& key) const
    {
        Config<T> config;
        auto it = m_configs.find(key);
        if ( m_configs.end() == it )
        {
            config.found = false;
            return config;
        }
        config.found = true;
        config.data = it->second->GetPtr<T>();
        return config;
    }

public:
    void Remove(const std::string&);
    void GetConfigs(ConfigsMap& map) const;

private:
    ConfigsMap m_configs;
};

#endif // ! __TYPES_CONFIGS_HXX__

#include "ConfigurationBase.hpp"

namespace EvelEngine {
    ConfigurationBase::ConfigurationBase(const std::string& filepath) : _filepath(filepath)
    {

    }

    ConfigurationBase::~ConfigurationBase()
    {

    }

    const std::string& ConfigurationBase::filepath() const 
    {
        return _filepath;
    }

    void ConfigurationBase::read()
    {

    }

    void ConfigurationBase::defineOption(const std::string& name, Poco::DynamicAny value)
    {
        ConfigurationOption c;
        if (!value.isEmpty()) {
            c.value = value;
        }
        c.name = name;
        _options.push_back(c);
    }

    ConfigurationOption* ConfigurationBase::get(const std::string& name) 
    {
        for (auto it = _options.begin(); it != _options.end(); it++)
        {
            if ((*it).name == name) {
                return &(*it);
                //size_t index = std::distance(_options.begin(), it);
                //if (index < _options.size()) return _options.at(index);
            }
        }
        return nullptr;
    }
}

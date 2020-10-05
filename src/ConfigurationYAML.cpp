#include "ConfigurationYAML.hpp"

namespace EvelEngine 
{
    ConfigurationYAML::ConfigurationYAML(const std::string& filepath) : ConfigurationBase(filepath)
    {

    }

    ConfigurationYAML::~ConfigurationYAML()
    {

    }

    void ConfigurationYAML::read()
    {
        // TODO: Check if file exists and accessible
        if (_log) _log->info("Reading configuration file {0}", _filepath);

        YAML::Node config = YAML::LoadFile(_filepath);
    }
}

#ifndef __CONFIGURATION_YAML_HPP__
#define __CONFIGURATION_YAML_HPP__ 

#include "ConfigurationBase.hpp"

namespace EvelEngine {
    class ConfigurationYAML : public ConfigurationBase 
    {
        public:
            ConfigurationYAML(const std::string& filepath);
            ~ConfigurationYAML();
            void read();
        private:
    };
}

#endif

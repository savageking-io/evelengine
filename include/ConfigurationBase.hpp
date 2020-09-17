#ifndef __CONFIGURATION_BASE_HPP__
#define __CONFIGURATION_BASE_HPP__

#include <vector>
#include <string>
#include "Poco/DynamicAny.h"

namespace EvelEngine {

    enum ConfigurationOptionType {
        COT_INT = 0,
        COT_STRING,
        COT_FLOAT
    };

    class ConfigurationOption {
        public:
            Poco::DynamicAny value;
            std::string name;
    };

    class ConfigurationBase
    {
        public:
            ConfigurationBase(const std::string& filepath);
            ~ConfigurationBase();
            const std::string& filepath() const;
            virtual void read();
            void defineOption(const std::string& name, Poco::DynamicAny value);
            ConfigurationOption* get(const std::string& name);
        private:
            std::string _filepath;
            std::vector<ConfigurationOption> _options;
    };
}

#endif

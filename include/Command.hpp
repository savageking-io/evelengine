#ifndef __EVEL_ENGINE_CONSOLE_COMMAND_HPP__
#define __EVEL_ENGINE_CONSOLE_COMMAND_HPP__

#include <string>

namespace EvelEngine
{
    class Command 
    {
        public:
        virtual bool handleCommand(const std::string& command);
        virtual const std::string& output() const;
        protected:
        std::string _output;
    };
}

#endif

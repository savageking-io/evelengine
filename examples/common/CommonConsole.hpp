#ifndef __COMMON_CONSOLE_HPP__
#define __COMMON_CONSOLE_HPP__

#include "Engine.hpp"
#include "Command.hpp"

class CommonConsole : public EvelEngine::Command
{
    public:
        CommonConsole();
        ~CommonConsole();
        bool handleCommand(const std::string& cmd);
    private:
        EvelEngine::Engine* _engine;
};

#endif

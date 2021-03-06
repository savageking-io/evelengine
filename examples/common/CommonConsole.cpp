#include "CommonConsole.hpp"

CommonConsole::CommonConsole()
{
    _engine = EvelEngine::Engine::get();
}

CommonConsole::~CommonConsole()
{

}

bool CommonConsole::handleCommand(const std::string& cmd)
{
    if (cmd == "quit")
    {
        _engine->simulation()->setState(EvelEngine::SIM_SHUTDOWN);
        return true;
    } 
    else if (cmd == "refresh")
    {
        _engine->resize();
        return true;
    }
    return false;
}

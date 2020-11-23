#ifndef __NOISE_CONSOLE_HPP___
#define __NOISE_CONSOLE_HPP__

#include "Engine.hpp"
#include "noise.hpp"
#include "Command.hpp"

class NoiseConsole : public EvelEngine::Command
{
    public:
        NoiseConsole(NoiseExample* noise);
        ~NoiseConsole();
        bool handleCommand(const std::string& cmd);
    private:
        EvelEngine::Engine* _engine;
        NoiseExample* _noise;

};

#endif

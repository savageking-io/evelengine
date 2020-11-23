#include "NoiseConsole.hpp"

#include "Poco/StringTokenizer.h"
#include "Poco/NumberParser.h"

#include "Scene.hpp"

NoiseConsole::NoiseConsole(NoiseExample* noise) : _noise(noise)
{
    _engine = EvelEngine::Engine::get();
}

NoiseConsole::~NoiseConsole()
{

}

bool NoiseConsole::handleCommand(const std::string& cmd)
{
    if (cmd.substr(0, 7) == "octaves") 
    {

    }
    else if (cmd.substr(0, 4) == "seed")
    {
        _engine->log()->info("Received `seed` command");
        Poco::StringTokenizer t(cmd, " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);

        if (t.count() != 2) 
        {
            _output = "seed expects 1 argument";
            _engine->log()->error("Wrong number of arguments for `seed`: {0}", t.count());
            return true;
        }

        auto cmd = t.begin();
        cmd++;

        _engine->log()->info("New seed requested: {0}", (*cmd));

        uint32_t newSeed = Poco::NumberParser::parse((*cmd));
        
        _noise->clear();
        _noise->params()->seed = newSeed;
        _noise->generate();

        return true;
    }
    else if (cmd == "clear")
    {
        _engine->scene()->clear();
        return true;
    }
    return false;
}

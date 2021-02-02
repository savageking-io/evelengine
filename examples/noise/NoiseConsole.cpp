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
        Poco::StringTokenizer t(cmd, " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
        if (t.count() != 2)
        {
            _output = "octaves expects 1 arguments";
            return true;
        }

        auto arg = t.begin();
        arg++;
        
        int octaves = Poco::NumberParser::parse((*arg));
        if (octaves != 1 && octaves != 8 && octaves != 64)
        {
            _output = "octaves must be 0..8..64";
            return true;
        }

        _noise->clear();
        _noise->params()->octaves = octaves;
        return true;
    }
    else if (cmd.substr(0, 4) == "freq")
    {
        Poco::StringTokenizer t(cmd, " ", Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);

        if (t.count() != 2)
        {
            _output = "freq expects 1 arguments";
            return true;
        }

        auto arg = t.begin();
        arg++;

        float freq = Poco::NumberParser::parseFloat((*arg));
        _noise->clear();
        _noise->params()->freq = freq;
        //_noise->generate();
        return true;
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

        auto arg = t.begin();
        arg++;

        _engine->log()->info("New seed requested: {0}", (*arg));

        uint32_t newSeed = Poco::NumberParser::parse((*arg));
        
        _noise->clear();
        _noise->params()->seed = newSeed;
        //_noise->generate();

        return true;
    }
    else if (cmd == "clear")
    {
        _engine->scene()->clear();
        return true;
    }
    return false;
}

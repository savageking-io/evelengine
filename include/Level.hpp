#ifndef __EVEL_ENGINE_LEVEL_HPP__
#define __EVEL_ENGINE_LEVEL_HPP__

#include <iostream>

#include "Command.hpp"

namespace EvelEngine
{
    class Level : public Command
    {
        public:
        Level(const std::string& seed);
        ~Level();
        bool handleCommand(const std::string& command);
        std::string getSeed();
        void build();
        double perlin(double x, double y, double z);
        private:
        std::string _seed;
    };
}

#endif

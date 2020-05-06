#include "Level.hpp"

namespace EvelEngine
{
    Level::Level(const std::string& seed) : _seed(seed)
    {

    }

    Level::~Level()
    {

    }

    bool Level::handleCommand(const std::string& command)
    {
        
        return false;
    }

    std::string Level::getSeed()
    {
        return _seed;
    }

    void Level::build()
    {

    }

    double Level::perlin(double x, double y, double z)
    {
		return 0.0;
    }

}

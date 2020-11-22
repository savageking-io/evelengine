#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "Engine.hpp"

#include "Player.hpp"
#include "Chunk.hpp"

#include <vector>

class World
{
    public:
        World(Player *p);
        ~World();
        void generate();
    protected:
        void generate_water();
    private:
        Player* _p;
        EvelEngine::Log* _log;
        std::vector<Chunk> _chunks;
};

#endif

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Engine.hpp"

class Player
{
    public:
        // max_x and max_y specify how far from 0, 0 player can spawn
        Player(int max_x, int max_y);
        ~Player();
        int x();
        int y();
    private:
        int _x;
        int _y;
        EvelEngine::Log* _log;
};

#endif

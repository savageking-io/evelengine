#include "Player.hpp"

#include "Poco/Random.h"

Player::Player(int max_x, int max_y)
{
    _log = EvelEngine::Engine::get()->log();     
    _log->info("Creating Player");

    Poco::Random rnd;
    rnd.seed();
    _x = rnd.next(max_x);
    _y = rnd.next(max_y);
    _log->info("Player spawn position: {0} {1}", _x, _y);
}

Player::~Player()
{

}

int Player::x()
{
    return _x;
}

int Player::y()
{
    return _y;
}

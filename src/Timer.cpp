#include "Timer.hpp"
#include "Engine.hpp"

namespace EvelEngine
{

    Timer::Timer(const std::string& id) : _id(id)
    {
        Engine::get()->log()->info("Initializing new timer {0}", id);
        _start = 0;
        _ticks = 0;
        _running = false;
    }

    Timer::~Timer()
    {

    }

    void Timer::start()
    {
        Engine::get()->log()->debug("Timer {0} started", _id);
        _running = true;
        _start = SDL_GetTicks();
    }

    void Timer::stop()
    {
        Engine::get()->log()->debug("Timer {0} stopped", _id);
        _running = false;
        _start = 0;
    }

    void Timer::reset()
    {
        stop();
        start();
    }

    Uint32 Timer::ticks()
    {
        Uint32 t = 0;

        if (_running)
        {
            t = SDL_GetTicks() - _start;
        }

        return t;
    }

    bool Timer::running()
    {
        return _running;
    }

}

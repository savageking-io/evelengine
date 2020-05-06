#ifndef __EVEL_ENGINE_TIMER_HPP__
#define __EVEL_ENGINE_TIMER_HPP__

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Log.hpp"

namespace EvelEngine
{
    class Timer
    {
        public:
            Timer(const std::string& id);
            ~Timer();
            void start();
            void stop();
            void reset();

            bool running();

            Uint32 ticks();

        private:
            std::string _id;
            bool _running;
            Uint32 _ticks;
            Uint32 _start;
    };
}

#endif

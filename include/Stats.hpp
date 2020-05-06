#ifndef __EVEL_ENGINE_STATS_HPP__
#define __EVEL_ENGINE_STATS_HPP__

#include <sstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Log.hpp"
#include "Timer.hpp"

namespace EvelEngine
{
    ///
    /// \class Stats 
    /// \brief Render's different statistics like FPS
    class Stats
    {
        public:
            Stats();
            ~Stats();
            void load();
            void enable();
            void disable();
            void update();
            void frameStart();
            void frameEnd();
            void render();

        private:
            bool _enabled;
            int _fps;
            int _frames;
            Log* _log;
            TTF_Font* _font;                                ///< Current font used
            SDL_Rect* _rect;                                ///< 
            SDL_Texture* _texture;
            SDL_Renderer* _renderer;
            Timer* _timer;
            Uint32 _lastUpdate;
            int _width;
            int _height;
    };
}

#endif

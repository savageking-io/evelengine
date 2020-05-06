#ifndef __EVEL_ENGINE_TEXTURE_HPP__
#define __EVEL_ENGINE_TEXTURE_HPP__

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "Log.hpp"

namespace EvelEngine 
{
    class Texture 
    {
        public:
        Texture(SDL_Renderer* renderer, Log* log);
        ~Texture();
        bool load(const std::string& path);
        SDL_Texture* get();
        int width();
        int height();
        const std::string& id() const;
        private:
        SDL_Renderer* _renderer;
        Log* _log;
        std::string _filename;
        SDL_Texture* _texture;
        int _width;
        int _height;
    };
}

#endif

#ifndef __EVEL_ENGINE_PRIMITIVES_HPP__
#define __EVEL_ENGINE_PRIMITIVES_HPP__


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "Object.hpp"
#include "Texture.hpp"

namespace EvelEngine {
    class Primitives : public Object {
        public:
            Primitives(const std::string& id, SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color, Log* log);
            ~Primitives();
            virtual void render(Camera* camera, double delta) = 0;
            virtual std::shared_ptr<Texture> draw();
            void setColor(SDL_Color color);
            SDL_Color color();
        protected:
            SDL_Color _color;
    };
}

#endif

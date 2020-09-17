#ifndef __EVEL_ENGINE_POINT_HPP__
#define __EVEL_ENGINE_POINT_HPP__

#include "Primitives.hpp"

namespace EvelEngine {
    class Point : public Primitives
    {
        public:
            Point(const std::string& id, SDL_Renderer* renderer, int x, int y, SDL_Color color, Log* log);
            ~Point();
            void render(Camera* camera, double delta);
    };

    std::shared_ptr<Point> NewPoint(const std::string& id, int x, int y, SDL_Color color);
}

#endif

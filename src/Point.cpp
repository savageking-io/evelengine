#include "Point.hpp"
#include "Engine.hpp"

namespace EvelEngine {
    Point::Point(const std::string& id, SDL_Renderer* renderer, int x, int y, SDL_Color color, Log* log) : Primitives(id, renderer, x, y, 1, 1, color, log)
    {
        if (_log) _log->debug("Spawning new point at {0} {1}", _x, _y);
    }

    Point::~Point()
    {

    }

    void Point::render(Camera* camera, double delta)
    {
        if (!_renderer) { return; }
        SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
        SDL_RenderDrawPoint(_renderer, _x, _y);
    }

    std::shared_ptr<Point> NewPoint(const std::string& id, int x, int y, SDL_Color color)
    {
        auto engine = Engine::get();
        auto p = std::make_shared<Point>(id, engine->renderer(), x, y, color, engine->log());
        return p;
    }
}

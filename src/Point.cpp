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

    std::shared_ptr<Texture> Point::draw()
    {
        auto texture = std::make_shared<Texture>(_renderer, _log);
        texture->createBlank(_id, 1, 1);
        if (SDL_SetRenderTarget(_renderer, texture->get()) != 0)
        {
            _log->error("Failed to switch render target: {0}", SDL_GetError());
            SDL_SetRenderTarget(_renderer, NULL);
            return texture;
        }
        if (SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a) != 0)
        {
            _log->error("Failed to set render draw color: {0}", SDL_GetError());
            SDL_SetRenderTarget(_renderer, NULL);
            return texture;
        }
        if (SDL_RenderDrawPoint(_renderer, _x, _y) != 0) 
        {
            _log->error("Failed to draw point: {0}", SDL_GetError());
            SDL_SetRenderTarget(_renderer, NULL);
            return texture;
        }
        SDL_SetRenderTarget(_renderer, NULL);
        return texture;
    }

    std::shared_ptr<Point> NewPoint(const std::string& id, int x, int y, SDL_Color color)
    {
        auto engine = Engine::get();
        auto p = std::make_shared<Point>(id, engine->renderer(), x, y, color, engine->log());
        return p;
    }
}

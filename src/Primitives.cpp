#include "Primitives.hpp"

namespace EvelEngine
{

    Primitives::Primitives(const std::string &id, SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color, Log *log)
        : Object(id, nullptr, renderer, "", log)
    {
        _position.position.x = x;
        _position.position.y = y;
        _position.size.x = w;
        _position.size.y = h;
        _color = color;
    }

    Primitives::~Primitives()
    {
    }

    std::shared_ptr<Texture> Primitives::draw()
    {
    }

    void Primitives::setColor(SDL_Color color)
    {
        _color = color;
    }

    SDL_Color Primitives::color()
    {
        return _color;
    }

} // namespace EvelEngine

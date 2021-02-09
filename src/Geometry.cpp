#include "Geometry.hpp"

namespace EvelEngine
{
    Vector2D::Vector2D(int x, int y) : x(x), y(y)
    {

    }

    void Vector2D::normalize()
    {
        int magnitude = this->magnitude();
        x /= magnitude;
        y /= magnitude; 
    }

    Rect2D::Rect2D(Vector2D position, Vector2D size) : position(position), size(size)
    {

    }

    Rect2D::Rect2D(int x, int y, int w, int h) : position(x ,y), size(w, h)
    {

    }

    const SDL_Rect Rect2D::rect() const
    {
        return SDL_Rect{position.x, position.y, size.x, size.y};
    }
}
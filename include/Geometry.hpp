#ifndef __GEOMETRY_HPP__
#define __GEOMETRY_HPP__

#include <math.h>

#include <SDL2/SDL.h>

namespace EvelEngine
{

    class Vector2D
    {
    public:
        int x;
        int y;
        Vector2D(int x, int y);
        inline int magnitude() { return sqrt(x * x + y * y); }
        inline int dot(Vector2D vec) const { return x * vec.x + y * vec.y; }
        inline Vector2D cross(Vector2D vec) const { return Vector2D(y * vec.y, x * vec.x); }
        void normalize();
        inline Vector2D operator*(int num) const { return Vector2D(x * num, y * num); };
        inline Vector2D operator+(const Vector2D &vec) const { return Vector2D(x + vec.x, y + vec.y); };
        inline Vector2D operator-(const Vector2D &vec) const { return Vector2D(x - vec.x, y - vec.y); };
    };

    class Rect2D
    {
    public:
        Vector2D position;
        Vector2D size;
        Rect2D(Vector2D position, Vector2D size);
        Rect2D(int x, int y, int w, int h);
        const SDL_Rect rect() const;
    };

} // namespace EvelEngine

#endif
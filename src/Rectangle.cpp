#include "Rectangle.hpp"

namespace EvelEngine {
Rectangle::Rectangle(const std::string& id, SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color, Log* log)
    : Primitives(id, renderer, x, y, w, h, color, log)
{
  
}

Rectangle::~Rectangle()
{
}

void Rectangle::render(Camera* camera, double delta)
{
  // TODO: Optimize this
  _rect.x = _x;
  _rect.y = _y;
  _rect.w = _w;
  _rect.h = _h;

  SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
  SDL_RenderFillRect(_renderer, &_rect);
}

}

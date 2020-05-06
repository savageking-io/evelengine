#ifndef __EVEL_ENGINE_RECTANGLE_HPP__
#define __EVEL_ENGINE_RECTANGLE_HPP__

#include "Primitives.hpp"

namespace EvelEngine {
  class Rectangle : public Primitives
  {
    public:
      Rectangle(const std::string& id, SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color, Log* log);
      ~Rectangle();
      void render(Camera* camera, double delta);
      
    private:
      SDL_Rect _rect;
  };
}

#endif

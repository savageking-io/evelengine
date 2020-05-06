#ifndef __EVEL_ENGINE_TEXT_HPP__
#define __EVEL_ENGINE_TEXT_HPP__

#include "Object.hpp"
#include "Font.hpp"

namespace EvelEngine {
  class Text : public Object {
    public:
      Text(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log);
      ~Text();
      void setColor(SDL_Color color);
      bool load();
      void render(Camera* camera, double delta);
      void update();
    private:
      Font* _font;
      SDL_Texture* _texture;
      SDL_Color _color;
  };
}

#endif

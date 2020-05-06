#ifndef __EVEL_ENGINE_FONT_HPP__
#define __EVEL_ENGINE_FONT_HPP__

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Log.hpp"

namespace EvelEngine {
  class Font 
  {
    public:
      Font(const std::string& path, int size, Log* log);
      ~Font();
      bool load();
      TTF_Font* get();
      int size();
    private:
      std::string _id;
      int _size;
      TTF_Font* _font;
      Log* _log;
  };
}

#endif

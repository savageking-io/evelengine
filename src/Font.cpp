#include "Font.hpp"

namespace EvelEngine {

  Font::Font(const std::string& path, int size, Log* log) : 
  _id(path), _size(size), _log(log)
  {

  }

  Font::~Font()
  {
    if (_font != NULL) TTF_CloseFont(_font);
  }

  bool Font::load()
  {
    _font = TTF_OpenFont(_id.c_str(), 15);
    if (_font == NULL) {
      _log->error("Failed to load font: {0}", TTF_GetError());
      return false;
    }
    return true;
  }

  TTF_Font* Font::get()
  {
    return _font;
  }

  int Font::size()
  {
    return _size;
  }
}

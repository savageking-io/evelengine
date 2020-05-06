#include "Texture.hpp"

namespace EvelEngine {

Texture::Texture(SDL_Renderer* renderer, Log* log)
    : _renderer(renderer)
    , _log(log)
{
}

Texture::~Texture()
{
}

bool Texture::load(const std::string& path)
{
    if (_renderer == NULL) {
        _log->error("Can't load texture: renderer is null");
        return false;
    }
    _filename = path;
    SDL_Surface* img = IMG_Load(_filename.c_str());
    if (img == NULL) {
        _log->error("Failed to load texture from file {0}: {1}", _filename, IMG_GetError());
        return false;
    }

    if ((_texture = SDL_CreateTextureFromSurface(_renderer, img)) == NULL) {
        _log->error("Failed to create texture from file {0}: {1}", _filename, IMG_GetError());
        return false;
    }

    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
    SDL_FreeSurface(img);
    return true;
}

SDL_Texture* Texture::get()
{
  return _texture;
}

int Texture::width()
{
  return _width;
}

int Texture::height()
{
  return _height;
}

const std::string& Texture::id() const 
{
  return _filename;
}

}

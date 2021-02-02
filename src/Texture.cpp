#include "Texture.hpp"

namespace EvelEngine
{

  Texture::Texture(SDL_Renderer *renderer, Log *log)
      : _renderer(renderer), _log(log)
  {
    _width = -1;
    _height = -1;
    _texture = nullptr;
    _filename = "";
  }

  Texture::~Texture()
  {
    if (_texture != NULL)
    {
      _log->debug("Destroying texture: {0}", _filename);
      SDL_DestroyTexture(_texture);
    }
  }

  bool Texture::load(const std::string &path)
  {
    if (_renderer == NULL)
    {
      _log->error("Can't load texture: renderer is null");
      _texture = nullptr;
      return false;
    }
    _filename = path;
    SDL_Surface *img = IMG_Load(_filename.c_str());
    if (img == NULL)
    {
      _log->error("Failed to load texture from file {0}: {1}", _filename, IMG_GetError());
      _texture = nullptr;
      return false;
    }

    if ((_texture = SDL_CreateTextureFromSurface(_renderer, img)) == NULL)
    {
      _log->error("Failed to create texture from file {0}: {1}", _filename, IMG_GetError());
      _texture = nullptr;
      return false;
    }

    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
    SDL_FreeSurface(img);
    return true;
  }

  bool Texture::create(const std::string &name, SDL_Surface *surface)
  {
    _filename = name;
    _log->debug("Creating texture from surface: {0}", _filename);
    if (surface == NULL)
    {
      _log->error("Can't create texture: null surface");
      return false;
    }
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (_texture == NULL)
    {
      _log->error("Failed to create texture from surface: {0}", SDL_GetError());
      return false;
    }
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
    return true;
  }

  bool Texture::createBlank(const std::string &name, int width, int height)
  {
    _filename = name;
    _log->debug("Creating blank texture: {0}", _filename);
    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (_texture == NULL)
    {
      _log->error("Failed to create texture: {0}", SDL_GetError());
      return false;
    }
    _width = width;
    _height = height;
    return true;
  }

  void Texture::draw(std::vector<TextureData> data)
  {

    SDL_SetRenderTarget(_renderer, _texture);
    for (auto it = data.begin(); it != data.end(); ++it)
    {
      SDL_Rect src{(*it).sx, (*it).sy, (*it).sw, (*it).sh};
      SDL_Rect dst{(*it).px, (*it).py, (*it).pw, (*it).ph};
      SDL_RenderCopy(_renderer, (*it).texture, &src, &dst);
    }
    SDL_SetRenderTarget(_renderer, NULL);
  }

  SDL_Texture *Texture::get()
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

  const std::string &Texture::id() const
  {
    return _filename;
  }

} // namespace EvelEngine

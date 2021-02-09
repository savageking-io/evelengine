#include "Texture.hpp"
#include "Engine.hpp"

namespace EvelEngine
{

    std::shared_ptr<Texture> NewTexture(const std::string &id)
    {
        std::shared_ptr<Texture> texture = std::make_shared<Texture>(Engine::get()->renderer(), Engine::get()->log());
        return texture;
    }

    Texture::Texture(SDL_Renderer *renderer, Log *log)
        : _renderer(renderer), _log(log), _src(0, 0, 0, 0), _dst(0, 0, 0, 0)
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
        _log->debug("Creating blank texture {0} Width {1} Height {2}", _filename, width, height);
        _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        _width = width;
        _height = height;
        if (_texture == NULL)
        {
            _log->error("Failed to create texture: {0}", SDL_GetError());
            return false;
        }
        return true;
    }

    void Texture::draw(std::vector<std::shared_ptr<Texture>> data)
    {
        target();
        SDL_RenderClear(_renderer);
        for (auto it = data.begin(); it != data.end(); ++it)
        {
            _log->debug("Adding new texture to {0}", _filename);
            auto src = (*it)->source().rect();
            auto dst = (*it)->destination().rect();
            SDL_RenderCopy(_renderer, (*it)->get(), &src, &dst);
        }
        EvelEngine::Engine::get()->resetRenderTarget();
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

    void Texture::target()
    {
        SDL_SetRenderTarget(_renderer, _texture);
    }

    void Texture::source(int x, int y, int w, int h)
    {
        _src.position.x = x;
        _src.position.y = y;
        _src.size.x = w;
        _src.size.y = h;
    }

    void Texture::source(Rect2D src)
    {
        _src = src;
    }

    void Texture::destination(int x, int y, int w, int h)
    {
        _dst.position.x = x;
        _dst.position.y = y;
        _dst.size.x = w;
        _dst.size.y = h;
    }

    void Texture::destination(Rect2D dst)
    {
        _dst = dst;
    }

    Rect2D Texture::source()
    {
        return _src;
    }

    Rect2D Texture::destination()
    {
        return _dst;
    }

} // namespace EvelEngine

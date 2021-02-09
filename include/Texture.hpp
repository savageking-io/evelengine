#ifndef __EVEL_ENGINE_TEXTURE_HPP__
#define __EVEL_ENGINE_TEXTURE_HPP__

#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "Log.hpp"
#include "Geometry.hpp"

namespace EvelEngine
{

    struct TextureData
    {
        SDL_Texture *texture;
        Rect2D source;
        Rect2D dest;
        TextureData() : source(Rect2D(0, 0, 0, 0)), dest(Rect2D(0, 0, 0, 0)) {}
    };

    ///
    /// \class Texture
    /// \brief A texture used by game objects
    ///
    /// Textures can be loaded from an image file using SDL_Image or
    /// created on the fly
    class Texture
    {
    public:
        //! Constructor
        /*
            * \param renderer - SDL_Renderer
            * \param log - Log object
            */
        Texture(SDL_Renderer *renderer, Log *log);
        ~Texture();
        bool load(const std::string &path);
        bool create(const std::string &name, SDL_Surface *surface);
        bool createBlank(const std::string &name, int width, int height);
        void draw(std::vector<std::shared_ptr<Texture>> data);
        SDL_Texture *get();
        int width();
        int height();
        const std::string &id() const;
        void target();
        void source(int x, int y, int w, int h);
        void source(Rect2D src);
        void destination(int x, int y, int w, int h);
        void destination(Rect2D dst);
        Rect2D source();
        Rect2D destination();

    private:
        Rect2D _src;          // Position and size of this texture relative to the object or render target
        Rect2D _dst;     // Destination coordinates if this textures is being rendered directly to another texture
        SDL_Renderer *_renderer; // SDL Renderer
        Log *_log;
        std::string _filename;
        SDL_Texture *_texture;
        int _width;
        int _height;
    };

    std::shared_ptr<Texture> NewTexture(const std::string &name);
} // namespace EvelEngine

#endif

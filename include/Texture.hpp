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

namespace EvelEngine
{

    struct TextureData
    {
        SDL_Texture *texture;
        int sx;
        int sy;
        int sw;
        int sh;
        int px;
        int py;
        int pw;
        int ph;
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
        bool create(const std::string& name, SDL_Surface *surface);
        bool createBlank(const std::string& name, int width, int height);
        void draw(std::vector<TextureData> data);
        SDL_Texture *get();
        int width();
        int height();
        const std::string &id() const;

    private:
        SDL_Renderer *_renderer;
        Log *_log;
        std::string _filename;
        SDL_Texture *_texture;
        int _width;
        int _height;
    };
} // namespace EvelEngine

#endif

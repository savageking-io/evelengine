#ifndef __EVEL_ENGINE_OBJECT_HPP__
#define __EVEL_ENGINE_OBJECT_HPP__

#include <iostream>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "Log.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "Texture.hpp"
#include "Velocity.hpp"

namespace EvelEngine {

    class Engine;

    ///
    /// \class Object
    /// \brief Static Game Object
    /// 
    /// Base class for all game objects. 
    /// 
    /// \sa AnimatedObject
    class Object {
        public:
            //! Constructor
            /*
             * \param id - Unique ID of the object
             * \param manager - ResourceManager
             * \param renderer - SDL_Renderer
             * \param filename - Path to texture
             * \param log - Log object
             */
            Object(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log);

            //! Destructor
            virtual ~Object();
            virtual bool load();
            virtual void render(Camera* camera, double delta);

            void attach();
            void detach();
            bool loaded();
            void hide();
            void show();

            // setters
            void setFilename(const std::string& filename);
            void setX(int x);
            void setY(int y);
            void setWidth(int w);
            void setHeight(int h);
            void setPosition(int x, int y);

            // getters
            int x();
            int y();
            int width();
            int height();
            const std::string& id() const;
            Velocity* velocity();

        protected:
            std::string _id; // Object ID. Not guarantted to be unique within any scope
            std::string _filename; // Filename of the object if any
            SDL_Renderer* _renderer; // Renderer that is passed to underlying elements
            Texture* _texture;
            int _x;
            int _y;
            int _w;
            int _h;

            Log* _log;
            bool _hidden; // hidden objects are not rendered
            bool _attached; // whether or not this object attached to camera
            bool _loaded; // whether or not this object was loaded
            ResourceManager* _manager; // resource manager used to load objects
            Velocity _velocity;
    };

    std::shared_ptr<Object> NewObject(const std::string& id, Engine* engine, const std::string& filename);
    std::shared_ptr<Object> NewObject(const std::string& id, const std::string& filename);
    std::shared_ptr<Object>  NewObjectInQueue(const std::string& id, Engine* engine, const std::string& filename);
};

#endif

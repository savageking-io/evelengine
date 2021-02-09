#ifndef __EVEL_ENGINE_SCENE_HPP__
#define __EVEL_ENGINE_SCENE_HPP__

#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "Log.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Primitives.hpp"
#include "Engine.hpp"
#include "Texture.hpp"

namespace EvelEngine {
    class Scene {
        public:
            //! Constructor
            Scene(const std::string& id, Log* log);

            //! Destructor
            ~Scene();

            //! Add new object to the scene
            /*!
             * Adds object to the scene. Objects will be rendered in the same order as 
             * they were added
             *
             * \param shared_ptr<Object>
             */
            void addObject(std::shared_ptr<Object> _object);

            //! Add scene to this scene
            /*!
             * This method will add provided scene as a child-scene
             *
             * \param shared_ptr<Scene>
             */
            void addScene(std::shared_ptr<Scene> scene);

            //! Renders scenes and objects
            /*!
             * Renders objects of this scene and then all
             * child scenes in the same order, that they was
             * added
             *
             * \param camera - Reference to camera object
             * \param double - Delta time
             */
            void render(Camera* camera, double delta);

            //! Find objects on specified coordinates
            /*!
             * Method goes through all object that this scene contains and
             * compare their coordinates to the ones, that was provided
             *
             * \param x coordinate
             * \param y coordinate
             * \return std::vector of found objects
             */
            std::vector<std::shared_ptr<Object>> findObjects(int x, int y);
            std::shared_ptr<Scene> findScene(const std::string& name);
            const std::string id() const;
            void clear();
            void hide();
            void show();
            bool isHidden();
            
            // std::shared_ptr<Texture> convertToTexture();
        private:
            std::vector<std::shared_ptr<Scene>>     _scenes;    ///< List of child scenes
            std::vector<std::shared_ptr<Object>>    _objects;   ///< List of attached objects
            Log*                                    _log;       ///< Logging subsystem
            std::string                             _id;        ///< ID of this scene
            bool _hidden;
    };

    std::shared_ptr<Scene> NewScene(const std::string& id);
};

#endif

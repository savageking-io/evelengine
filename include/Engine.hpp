#ifndef __EVEL_ENGINE_ENGINE_HPP__
#define __EVEL_ENGINE_ENGINE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <deque>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define __EVEL_WIN
#include "SDL.h"
#else
#define __EVEL_UNIX
#include "SDL2/SDL.h"
#endif

#include "Log.hpp"
#include "CommandInterface.hpp"
#include "Event.hpp"
#include "Level.hpp"
#include "Object.hpp"
#include "Seed.hpp"
#include "Simulation.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "FileSystem.hpp"
#include "Stats.hpp"

///
/// \namespace EvelEngine 
/// \brief Main namespace of the engine
/// 
namespace EvelEngine {

    class Scene;

    ///
    /// \class Engine
    /// \brief Main class of the engine
    ///
    class Engine {
        public:
            //! Returns a reference to the Engine
            static Engine* get();

            //! Engine intializer
            /*!
             * This method initializes Evel Engine by calling appropriate SDL initializators
             * and creating all objects required by the engine
             */
            void initialize();
            void deinitialize();

            //! Main game loop
            /*!
             * This is a main game loop
             */
            int run();
            void enableConsole();

            void resize();

            //! Returns width of the window
            /*!
             * \return int window width
             */
            int getWindowWidth();

            //! Returns height of the window
            /*!
             * \return int window height
             */
            int getWindowHeight();

            //! Sets width of the window
            /*!
             * \param int width in pixels
             */
            void setWindowWidth(int w);

            //! Sets height of the window
            /*!
             * \param int height in pixels
             */
            void setWindowHeight(int h);

            void enableFullscreen();

            void disableFullscreen();

            void toggleFullscreen();

            void setRenderSize(int w, int h);

            void resetRenderTarget();

            //! Returns a reference to SDL_Renderer
            /*!
             * \return SDL_Renderer
             */
            SDL_Renderer* renderer();

            //! Returns a reference to SDL_Window created by the engine
            /*!
             * \return SDL_Window
             */
            SDL_Window* window();

            //! Returns top-level scene
            /*!
             * This returns a top-level scene. All objects and other scenes that
             * is created must be attached to this scene or to another 
             * scene that is attached to it
             *
             * \return Scene
             */
            Scene* scene();

            //! Returns Simulation
            /*!
             * \return Simulation
             */
            Simulation* simulation();

            //! Returns a reference to a FileSystem
            /*
             * \return FS object
             * \sa FileSystem
             */
            FileSystem* fs();

            //! Returns a reference to an event subsystem
            /*!
             * \return Event
             */
            Event* event();

            //! Returns a reference to command line interface
            /*!
             * \return CommandInterface
             */
            CommandInterface* cli();

            //! Return a reference to game camera
            /*!
             * \return Camera
             */
            Camera* camera();

            //! Adds object to loading queue
            /*!
             * Loading queue gets handled during main loop iteration.
             * In order to not hang the game, we can add objects to 
             * load queue. Each frame this method will attempt to
             * load object. Later retuls can be checked by using 
             * Object::loaded
             *
             * \param Object to load
             */
            void addToQueue(std::shared_ptr<Object> obj);

            //! Returns a reference to logging subsystem
            /*!
             * \return Log
             */
            Log* log();

            //! Returns a reference to Resource Manager
            /*!
             * \return ResourceManager
             */
            ResourceManager* manager();
        protected:

            //! Constructor
            Engine(); 

            //! Constructor that accepts arguments
            Engine(std::vector<std::string> args);

            //! Destructor
            ~Engine();

            //! Load next item from queue
            /*!
             * This method executed on every tick and it 
             * attempts to load objects from queue
             *
             * \sa addToQueue()
             */
            void loadFromQueue(); 

            static Engine*              _self;              ///< Reference to Engine object
        private:
            std::vector<std::string>    _args;              ///< Command line arguments provided at startup
            SDL_Window* _window =       NULL;               ///< SDL Window object. Created during initialization
            SDL_Renderer* _renderer =   NULL;               ///< SDL Renderer object. Created during initialization
            Scene*                      _scene;             ///< Top-level scene, that contains sub-scenes. See Scene class
            Event*                      _event;             ///< Pointer to event subsystem. See Event class
            Camera*                     _camera;            ///< Game camera. See Camera
            ResourceManager*            _manager;           ///< Manager of game resources. See ResourceManager
            Simulation*                 _sim;               ///< Simulation controller. See Simulation
            FileSystem*                 _fs;                ///< File system subsystem
            bool                        _running;           ///< Whether engine is running or not
            CommandInterface*           _command;           ///< Command-line interface for game console
            Log*                        _log;               ///< Logging subsystem
            Stats*                      _stats;
            int                         _windowWidth;       ///< Window width
            int                         _windowHeight;      ///< Window height
            std::deque<std::shared_ptr<Object>>         _loadingQueue;      ///< Queue of game resources to be loaded on each frame
            bool _fullscreen;
    };
}

#endif

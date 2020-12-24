#include "Engine.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Scene.hpp"
#include "RuntimeStats.hpp"

namespace EvelEngine {

    Engine* Engine::_self = nullptr;

    Engine* Engine::get()
    {
        if (!_self) _self = new(Engine);
        return _self;
    }

    Engine::Engine()
    {
        _windowWidth = 1024;
        _windowHeight = 768;
        _fullscreen = false;

        _log = new(Log);
        _log->initialize();
        _running = false;
        _sim = new Simulation();
    }

    //! Constructor
    /**
     * Constructor initializes logging subsystem and Simulation
     *
     * \param vector<string> of arguments
     */
    Engine::Engine(std::vector<std::string> args) : Engine()
    {
        _args = args;
    }

    //! Destructor
    Engine::~Engine()
    {
        _log->info("Cleaning up");
        delete _command;
        delete _scene;
        delete _event;
        delete _manager;
        delete _camera;
        delete _log;
        delete _fs;
        TTF_Quit();
        SDL_Quit();
    }

    //! Engine initializer
    /**
     * This method should be called explicitely after Engine object creation
     *
     * initialize will init SDL2, SDL2 hinting, create window and renderer
     * Also it initializes font system (SDL) and set of essential objects
     */
    void Engine::initialize()
    {
        _log->info("Initializing SDL");
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            _log->critical("Failed to initialize SDL2: {0}", SDL_GetError());
            return;
        }

        _log->debug("Setting render scale quality hint");
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
            _log->critical("Failed to initialize SDL2 hinting: {0}", SDL_GetError());
            return;
        }

        _log->debug("Creating new window {0}x{1}", _windowWidth, _windowHeight);
        if ((_window = SDL_CreateWindow("My SDL Game", SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight,
                        SDL_WINDOW_RESIZABLE))
                == NULL) {
            _log->critical("Failed to initialize SDL2 window: ", SDL_GetError());
            return;
        }

        SDL_SetWindowSize(_window, _windowWidth, _windowHeight);

        // SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);


        // _surface = SDL_GetWindowSurface(_window);

        _log->debug("Creating SDL Renderer");
        if ((_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
            _log->critical("Failed to create SDL Renderer: ", SDL_GetError());
            return;
        }


        _log->debug("Initializing SDL TTF");
        if (TTF_Init() < 0) {
            _log->critical("Failed to initialize TTF: ", TTF_GetError());
            return;
        }
        const SDL_version *ttfv = TTF_Linked_Version();
        _log->info("SDL2 TTF Initialization completed. Version: {0}.{1}.{2}", ttfv->major, ttfv->minor, ttfv->patch);

        _log->debug("Initializing SDL Image");
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            _log->critical("Failed to initialize SDL Image: {0}", IMG_GetError());
            return;
        }
        const SDL_version *imgv = IMG_Linked_Version();
        _log->info("SDL2 Image Initialization completed. Version: {0}.{1}.{2}", imgv->major, imgv->minor, imgv->patch);

        //SDL_RenderSetLogicalSize(_renderer, 480, 270);
        SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x88, 0xFF);

        _fs = new FileSystem("", _log);
        _manager = new ResourceManager(_renderer, _fs, _log);
        _scene = new Scene("__top-level__", _log);
        _event = new Event();
        _camera = new Camera(_windowWidth, _windowHeight);
        _command = new CommandInterface("cli");
        _event->subscribe(_command);
        _stats = new Stats();
        _stats->load();
        _log->info("Initialization complete");
    }

    //! Deinitizing of the engine
    void Engine::deinitialize() { _log->info("Deinitializing engine"); }

    //! Main game loop
    int Engine::run()
    {
        if (_scene == nullptr) {
            _log->critical("Top-level scene is null. Forgot to initalize?");
            return -1;
        }

        RuntimeStats rs;
        rs.initialize();

        SDL_Event event;
        _running = true;
        _log->info("Starting main loop");
        Uint32 wait = 1000.0f/60;
        Uint32 frameStart = 0;
        Sint32 delay;

        // Implementing new counter
        Uint64 tick = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        double delta = 0;

        // SDL_RenderSetScale(_renderer, 4, 4);

        while (_sim->getState() != SIM_SHUTDOWN) {
            _stats->frameStart();
            last = tick;
            tick = SDL_GetPerformanceCounter();
            delta = (double)((tick - last) * 1000 / (double)SDL_GetPerformanceFrequency() );
            while (SDL_PollEvent(&event)) {
                _event->process(&event);
            }
            SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x88, 0xFF);
            SDL_RenderClear(_renderer);
            _scene->render(_camera, delta);
            // TODO: Lowercase Render method
            if (_command) _command->Render();
            if (_stats) _stats->render();

            // SDL_SetRenderDrawColor(_renderer, 0x30, 0x30, 0x30, 0xFF);
            // auto rect = SDL_Rect{20, 20, 30, 30};
            // SDL_RenderFillRect(_renderer, &rect);

            SDL_RenderPresent(_renderer);
            loadFromQueue();

            // Sleep
            delay = wait - (SDL_GetTicks() - frameStart);
            if (delay > 0) {
                SDL_Delay((Uint32)delay);
            }
            frameStart = SDL_GetTicks();
            _stats->frameEnd();
        }
        deinitialize();
        return 0;
    }

    void Engine::resize()
    {
        SDL_SetWindowSize(_window, _windowWidth, _windowHeight);
    }

    void Engine::enableConsole() {}

    //! Returns window width
    /**
     * \return int Window width
     */
    int Engine::getWindowWidth()
    {
        return _windowWidth;
    }

    //! Returns window height
    /**
     * \return int Window height
     */
    int Engine::getWindowHeight()
    {
        return _windowHeight;
    }

    void Engine::setWindowWidth(int w) 
    {
        _windowWidth = w;
    }

    void Engine::setWindowHeight(int h)
    {
        _windowHeight = h;
    }

    void Engine::enableFullscreen()
    {
        if (_window == NULL) return;
        if (_fullscreen) return;
        if (SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN) != 0)
        {
            _log->error("Failed to enable fullscreen: {0}", SDL_GetError());
            return;
        }
        _fullscreen = true;
    }

    void Engine::disableFullscreen()
    {
        if (_window == NULL) return;
        if (!_fullscreen) return;
        if (SDL_SetWindowFullscreen(_window, 0) != 0)
        {
            _log->error("Failed to disable fullscreen: {0}", SDL_GetError());
            return;
        }
        _fullscreen = false;
    }

    void Engine::toggleFullscreen()
    {
        if (_fullscreen) disableFullscreen();
        else enableFullscreen();
    }

    //! Returns reference to SDL_Renderer
    /**
     * \return SDL_Renderer Active Renderer
     */
    SDL_Renderer* Engine::renderer() { return _renderer; }

    SDL_Window* Engine::window() { return _window; }

    //! Returns reference to top-level Scene
    /*
     * \return Scene Top Level Scene
     */
    Scene* Engine::scene() { return _scene; }

    Simulation* Engine::simulation() { return _sim; }

    Event* Engine::event() { return _event; }

    CommandInterface* Engine::cli() { return _command; }

    Camera* Engine::camera() { return _camera; }

    FileSystem* Engine::fs() { return _fs; }

    void Engine::addToQueue(std::shared_ptr<Object> obj)
    {
        if (obj == nullptr) {
            _log->warn("Attempt to add null object to queue");
            return;
        }
        _log->info("Adding object {0} to queue", obj->id());
        _loadingQueue.push_back(obj);
    }

    void Engine::loadFromQueue()
    {
        if (_loadingQueue.size() == 0) return;
        auto obj = _loadingQueue.front();
        if (obj == nullptr) return;
        obj->load();
        _loadingQueue.pop_front();
    }

    Log* Engine::log()
    {
        return _log;
    }

    ResourceManager* Engine::manager()
    {
        return _manager;
    }

}

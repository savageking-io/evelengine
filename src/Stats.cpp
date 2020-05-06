#include "Stats.hpp"
#include "Engine.hpp"

namespace EvelEngine
{
    Stats::Stats()
    {
        _log = EvelEngine::Engine::get()->log();
        _renderer = EvelEngine::Engine::get()->renderer();
        _width = EvelEngine::Engine::get()->getWindowWidth();
        _height = EvelEngine::Engine::get()->getWindowHeight();
        _enabled = true;
        _texture = NULL;
        _log->info("Initializing stats subsystem");
        _fps = 0;
        _frames = 0;
        _lastUpdate = 0;
        _timer = new Timer("evel-engine-stats");
        _timer->start();
    }

    Stats::~Stats()
    {

    }

    void Stats::load()
    {
        // TODO: Unhardcode this
        _font = TTF_OpenFont("assets/fonts/fff.ttf", 30);
        if (_font == NULL) {
            _log->warn("Failed to load font: {0}", TTF_GetError());
            return;
        }
        _log->debug("Loaded stats font");
    }

    void Stats::enable()
    {
        _log->info("Statistics display enabled");
        _enabled = true;
    }

    void Stats::disable()
    {
        _log->info("Statistics display disabled");
        _enabled = false;
    }

    void Stats::update()
    {
        if (!_timer) return;

        Uint32 seconds = _timer->ticks() / 1000;
        if (seconds <= _lastUpdate) return;
            
        _lastUpdate = seconds;

        if (seconds > 0)
        {
            _fps = _frames / seconds;
        }
        std::stringstream buffer;
        buffer << _fps;

        SDL_Color color;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        auto surface = TTF_RenderUTF8_Solid(_font, buffer.str().c_str(), color);
        if (surface == NULL)
        {
            _log->error("Failed to render stats: {0}", TTF_GetError());
            return;
        }
        if ((_texture = SDL_CreateTextureFromSurface(_renderer, surface)) == NULL) {
            _log->error("Failed to create texture for CLI: {0}", SDL_GetError());
            return;
        }
        SDL_FreeSurface(surface);
    }

    void Stats::frameStart()
    {
        update();
    }

    void Stats::frameEnd()
    {
        _frames++;
    }

    void Stats::render()
    {
        if (!_enabled) return;
        if (!_font) return;
        if (!_texture) return;
        if (!_renderer) return;

        int w = 0;
        int h = 0;

        SDL_QueryTexture(_texture, NULL, NULL, &w, &h);
        SDL_Rect dst = { _width - 100, 20, w, h };
        SDL_RenderCopy(_renderer, _texture, NULL, &dst);
    }
}


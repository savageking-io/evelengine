#include "RuntimeStats.hpp"

namespace EvelEngine 
{
    RuntimeStats::RuntimeStats() {
        _log = Engine::get()->log();
        _videoDriver = "Unknown";
        _displayName = "Unknown";
    }

    RuntimeStats::~RuntimeStats() {}

    void RuntimeStats::initialize() 
    {
        if (_log) _log->info("Initializing Runtime Statistics subsystem");
        requestVideoDriver();
        requestDisplayName();
        requestWindowSize();
        requestViewport();
    }

    const std::string& RuntimeStats::videoDriver() const
    {
        return _videoDriver;
    }

    const std::string& RuntimeStats::displayName() const 
    {
        return _displayName;
    }

    void RuntimeStats::requestVideoDriver()
    {
        if (_log) _log->debug("Requesting Video Driver");
        _videoDriver = std::string(SDL_GetCurrentVideoDriver());
        if (_log) _log->info("Video Driver: {0}", _videoDriver);
    }

    void RuntimeStats::requestDisplayName()
    {
        if (_log) _log->debug("Requesting Display Name");
        _displayName = std::string(SDL_GetDisplayName(0));
        if (_log) _log->info("Display Name: {0}", _displayName);
    }

    void RuntimeStats::requestWindowSize()
    {
        if (_log) _log->debug("Requesting window size");
        int h = 0, w = 0;
        SDL_GetWindowSize(Engine::get()->window(), &w, &h);
        if (_log) _log->debug("Window Size is: {0}x{1}", w, h);
        h = w = 0;
        SDL_GL_GetDrawableSize(Engine::get()->window(), &w, &h);
        if (_log) _log->debug("Window Drawable Size is: {0}x{1}", w, h);
        h = w = 0;
        SDL_GetRendererOutputSize(Engine::get()->renderer(), &w, &h);
        if (_log) _log->debug("GL Render Output Size is: {0}x{1}", w, h);
    }

    void RuntimeStats::requestViewport()
    {
        if (_log) _log->debug("Requesting viewport");
        SDL_Rect r;
        SDL_RenderGetViewport(Engine::get()->renderer(), &r);
        if (_log) _log->debug("VP: {0} {1} {2} {3}", r.x, r.y, r.w, r.h);
    }
}

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
}

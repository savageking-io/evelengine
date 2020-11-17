#include "CommonEvents.hpp"

CommonEvents::CommonEvents(const std::string& id) : EvelEngine::EventBase(id)
{

}

CommonEvents::~CommonEvents()
{

}

void CommonEvents::handleKeyUp(SDL_Keycode key)
{
    if (key == SDLK_F3)
    {
        _engine->log()->debug("F3");
    }
}

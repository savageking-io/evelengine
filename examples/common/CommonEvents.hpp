#ifndef __COMMON_EVENTS_HPP__
#define __COMMON_EVENTS_HPP__

#include "Event.hpp"
#include "Engine.hpp"

class CommonEvents : public EvelEngine::EventBase
{
    public:
        CommonEvents(const std::string& id);
        ~CommonEvents();
        void handleKeyUp(SDL_Keycode key);
};

#endif

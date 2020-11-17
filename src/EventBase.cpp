#include "EventBase.hpp"
#include "Engine.hpp"

namespace EvelEngine
{
    EventBase::EventBase(const std::string& id) : _id(id)
    {
        _engine = Engine::get();
    }

    const std::string& EventBase::id() const
    {
        return _id;
    }

    void EventBase::handleKeyDown(SDL_Keycode key)
    {

    }

    void EventBase::handleKeyUp(SDL_Keycode key)
    {
 
    }

    void EventBase::handleText(char* characters)
    {
        
    }

    void EventBase::handleMouseMove(Uint32 state, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel)
    {
        
    }

    void EventBase::handleMouseDown(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks)
    {

    }

    void EventBase::handleMouseUp(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks)
    {
        
    }

    bool EventBase::operator==(const EventBase& eb) const
    {
        return (_id == eb.id());
    }
}

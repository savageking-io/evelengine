#include "Event.hpp"

namespace EvelEngine {
    Event::Event()
    {
    }

    Event::~Event()
    {
    }

    void Event::process(SDL_Event* event)
    {
        switch (event->type) {
            case SDL_KEYUP:
            keyUp(event->key.keysym.sym);
            break;
            case SDL_KEYDOWN:
            keyDown(event->key.keysym.sym);
            break;
            case SDL_TEXTINPUT:
            keyText(event->text.text);
            break;
            case SDL_MOUSEMOTION:
            mouseMotion(event->motion.state, event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
            break;
            case SDL_MOUSEBUTTONDOWN:
            mouseDown(event->button.button, event->button.state, event->button.x, event->button.y, event->button.clicks);
            break;
            case SDL_MOUSEBUTTONUP:
            mouseUp(event->button.button, event->button.state, event->button.x, event->button.y, event->button.clicks);
            break;
        }
        // switch (event->type) {
        //     case SDL_QUIT:
        //         _running = false;
        //         break;
        //     case SDL_KEYDOWN:
        //         if (event.key.keysym.sym == SDLK_q) {
        //             console->activate();
        //         }
        //         break;
        //     case SDL_TEXTINPUT:
        //         console->handleText(std::string(event.text.text));
        //         break;
        // };
    }

    void Event::subscribe(EventBase* ev)
    {
        _events.push_back(ev);
    }

    void Event::keyUp(SDL_Keycode key)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleKeyUp(key);
        }
    }

    void Event::keyDown(SDL_Keycode key)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleKeyDown(key);
        }
    }

    void Event::keyText(char* characters)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleText(characters); 
        }
    }

    void Event::mouseMotion(Uint32 state, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleMouseMove(state, x, y, xrel, yrel); 
        }
    }

    void Event::mouseDown(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleMouseDown(button, state, x, y, clicks); 
        }
    }

    void Event::mouseUp(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks)
    {
        for (auto it = _events.begin(); it != _events.end(); it++) {
            (*it)->handleMouseUp(button, state, x, y, clicks); 
        }
    }
}

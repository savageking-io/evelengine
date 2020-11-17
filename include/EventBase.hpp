#ifndef __EVEL_ENGINE_EVENT_BASE_HPP__
#define __EVEL_ENGINE_EVENT_BASE_HPP__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include <string>

namespace EvelEngine
{
    class Engine;

    class EventBase 
    {
        public:
            ///
            /// \class EventBase
            /// \brief Main class for user-defined events
            ///
            /// User must overwrite virtual methods that he wants 
            /// to use in his project. Then, during initialization
            /// of his project he must create an instance of his
            /// class and pass this object to Event::subscribe() method
            /// 
            /// \sa Event
            
            //! Constructor
            EventBase(const std::string& id);

            //! ID of the event class
            /*!
             * \return string - ID of the class
             */
            virtual const std::string& id() const;

            //! Handles Key Up event
            virtual void handleKeyUp(SDL_Keycode key);

            //! Handles Key Down event
            virtual void handleKeyDown(SDL_Keycode key);

            //! Handles Text Entry Event
            virtual void handleText(char* characters);

            //! Handles Mouse Mouse Event
            virtual void handleMouseMove(Uint32 state, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel);

            //! Handles Mouse Button Down Event
            virtual void handleMouseDown(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks);

            //! Handles Mouse Button Up Event
            virtual void handleMouseUp(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks);

            //! Compares event handler classes
            virtual bool operator==(const EventBase& eb) const;
        protected:
            std::string     _id;        ///< ID of current class
            Engine*         _engine;    ///< Reference to Engine
    };
}

#endif

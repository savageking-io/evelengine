#ifndef __EVEL_ENGINE_EVENT_HPP__
#define __EVEL_ENGINE_EVENT_HPP__

#include <iostream>
#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#include "EventBase.hpp"


namespace EvelEngine 
{
    typedef std::vector<EventBase*> EventSubscriptions;

    ///
    /// \class Event
    /// \brief Event subsystem for handling game events
    /// 
    /// To handle events in a game, developer must create a derivative class
    /// from EventBase and describe events that he wants to be handled.
    ///
    /// Next, during game initialization developer must create an object of 
    /// his class and pass this object to subscribe(). 
    /// 
    /// Developer may implement many different event systems for his project
    /// and send them to subscribe method. 
    /// Later, when event occurs, all the methods from user-defined class will
    /// be called in the same order they were add to subscribe method
    /// 
    /// \sa EventBase
    class Event
    {
        public:

            //! Constructor
            Event();

            //! Destructor
            ~Event();

            //! Processes events
            /*!
             * This method acceps incoming Event from main loop
             * and fires event method based on incoming event's type
             */
            void process(SDL_Event* event);

            //! Subsribes to an Event set
            /*!
             * Add new event definitions to the list of event handlers. 
             * Each method called by process() will go through a list of
             * event handlers and call appropriate methods if they were
             * redefined by the user
             *
             * \sa EventBase
             */
            void subscribe(EventBase* eb);

            //! Key Up Event
            void keyUp(SDL_Keycode key);

            //! Key Down Event
            void keyDown(SDL_Keycode key);

            //! Text Entered Event
            void keyText(char* characters);

            //! Mouse Motion Event
            void mouseMotion(Uint32 state, Sint32 x, Sint32 y, Sint32 xrel, Sint32 yrel);

            //! Mouse Button Down Event
            void mouseDown(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks);

            //! Mouse Button Up Event
            void mouseUp(Uint8 button, Uint32 state, Sint32 x, Sint32 y, int clicks);
        private:
            EventSubscriptions _events; ///< List of Event subscriptions
    };
}

#endif

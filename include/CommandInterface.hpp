#ifndef __EVEL_ENGINE_CONSOLE_HPP__
#define __EVEL_ENGINE_CONSOLE_HPP__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Command.hpp"
#include "EventBase.hpp"
#include "Object.hpp"
#include "Log.hpp"

namespace EvelEngine {

class Engine;

class CommandInterface : public EventBase {
public:
    CommandInterface(const std::string& id);
    virtual ~CommandInterface();
    void loadFont(const std::string& file, int size);
    void activate();
    void deactivate();
    void toggle();
    void handleText(const std::string& text);
    void updateInput();
    void Render();
    void subscribe(Command* commandClass);
    void process(const std::string& command);
    // configuration
    void setWidth(int w);
    void setHeight(int h);
    // events
    void handleKeyUp(SDL_Keycode key);
    void handleKeyDown(SDL_Keycode key);
    void handleText(char* characters);
protected:
    void updateHistory();
    // splitOutput will split string by newlines
    void splitOutput(const std::string& output);
    void addToHistory(const std::string& item);
private:
    void drawBackground();                      
    void drawHistory();
    int _fontSize;                                  ///< Current size of the font
    bool _isActive;                                 ///< Whether console is active or not
    SDL_Renderer* _renderer;                        ///< Reference to SDL_Renderer
    SDL_Texture* _inputTexture;                     ///< Texture of the input line
    std::vector<SDL_Texture*> _historyTexture;      ///< Textures of the history (past commands)
    SDL_Rect _rect;                                ///< 
    TTF_Font* _font;                                ///< Current font used
    std::string _buffer;                            ///< Input buffer
    std::vector<std::string> _history;              ///< Full history of previous output
    std::vector<std::string> _cmdHistory;           ///< History of all executed commands
    std::vector<Command*> _commands;                ///< Possible commands
    unsigned int _historyCursor = 0;                ///< Current history position
    Log* _log;                                      ///< Reference to loggin subsystem
};
}

#endif

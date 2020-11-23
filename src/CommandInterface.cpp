#include "CommandInterface.hpp"
#include "Engine.hpp"

namespace EvelEngine {

#define FONT_FILE "assets/fonts/minecraft.ttf"
#define FONT_SIZE 11

CommandInterface::CommandInterface(const std::string& id) : 
    EventBase(id), 
    _isActive(false)
{
    auto engine = Engine::get();
    _renderer = _engine->renderer();

    _log = engine->log();
    _log->info("Initializing command interface");

    //_rect = new SDL_Rect();
    _rect.h = engine->getWindowHeight() / 2;
    _rect.w = engine->getWindowWidth();
    _rect.x = 0;
    _rect.y = 0;

    _fontSize = FONT_SIZE;

    this->loadFont(FONT_FILE, _fontSize); 
}

CommandInterface::~CommandInterface()
{
    _log->info("Shutting down command interface");
    TTF_CloseFont(_font);
    //delete _rect;
}

void CommandInterface::loadFont(const std::string& file, int size)
{
    _font = TTF_OpenFont(file.c_str(), size);
    if (_font == NULL) {
        _log->warn("Failed to load font: {0}", TTF_GetError());
    }
}

void CommandInterface::activate()
{
    _log->debug("Activating console");
    _log->debug("Console rect: {0} {1} {2} {3}", _rect.x, _rect.y, _rect.w, _rect.h);
    _isActive = true;
    _historyCursor = 0;
    updateInput();
    SDL_StartTextInput();
}

void CommandInterface::deactivate()
{
    _log->debug("Deactivating console");
    _isActive = false;
    _historyCursor = 0;
    SDL_StopTextInput();
}

void CommandInterface::toggle()
{
    if (_isActive) {
        deactivate();
    } else {
        activate();
    }
}

void CommandInterface::handleText(const std::string& text)
{
    if (!_isActive)
        return;

    _buffer.append(text);
    updateInput();
}

void CommandInterface::updateInput()
{
    if (_renderer == NULL)
        return;
    if (_font == NULL)
        return;

    std::string buffer("");
    if (_buffer.length() == 0) {
        buffer = " ";
    } else {
        buffer.append(_buffer);
    }
    // Set console text to white
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    auto inputSurface = TTF_RenderUTF8_Solid(_font, buffer.c_str(), color);
    if (inputSurface == NULL) {
        _log->error("Failed to render CLI text: {0}", TTF_GetError());
        return;
    }
    if ((_inputTexture = SDL_CreateTextureFromSurface(_renderer, inputSurface)) == NULL) {
        _log->error("Failed to create texture for CLI: {0}", SDL_GetError());
        return;
    }
    SDL_FreeSurface(inputSurface);
}

void CommandInterface::updateHistory()
{
    if (_renderer == NULL)
        return;
    if (_font == NULL)
        return;

    if (_history.size() == 0) {
        _history.push_back("Welcome to the Game Console");
        _history.push_back("Type your commands here");
    }

    for (auto it = _historyTexture.begin(); it != _historyTexture.end(); it++) {
        SDL_DestroyTexture((*it));
    }
    _historyTexture.clear();

    std::vector<std::string>::iterator it = _history.begin();
    if (_history.size() > 10) {
        it = _history.end() - 9;
    }
    for (; it != _history.end(); it++) {
        // Set history text to grey
        SDL_Color color;
        color.r = 180;
        color.g = 180;
        color.b = 180;
        color.a = 255;
        auto inputSurface = TTF_RenderUTF8_Solid(_font, (*it).c_str(), color);
        if (inputSurface == NULL) {
            _log->error("Failed to render CLI text: {0}", TTF_GetError());
            return;
        }
        SDL_Texture* texture;
        if ((texture = SDL_CreateTextureFromSurface(_renderer, inputSurface)) == NULL) {
            _log->error("Failed to create texture for CLI: {0}", SDL_GetError());
            return;
        }
        _historyTexture.push_back(texture);
        SDL_FreeSurface(inputSurface);
    }
}

void CommandInterface::Render()
{
    if (!_isActive)
        return;
    if (_renderer == NULL)
        return;
    if (_font == NULL)
        return;
    if (_inputTexture == NULL)
        return;
    if (_history.size() == 0)
        updateHistory();

    // Draw console background
    drawBackground();

    SDL_Rect dst;
    int w = 0;
    int h = 0;
    int i = _rect.h - _fontSize - 5;
    for (auto it = _historyTexture.rbegin(); it != _historyTexture.rend(); it++) {
        if ((*it) == NULL)
            continue;

        SDL_QueryTexture((*it), NULL, NULL, &w, &h);
        i = i - h;
        dst = { 5, i, w, h };
        SDL_RenderCopy(_renderer, (*it), NULL, &dst);
    }

    SDL_QueryTexture(_inputTexture, NULL, NULL, &w, &h);
    dst = { 5, _rect.h - h, w, h };
    SDL_RenderCopy(_renderer, _inputTexture, NULL, &dst);
}

void CommandInterface::handleKeyDown(SDL_Keycode key)
{
    if (_isActive) {
        if (key == SDLK_RETURN) {
            // Handle command execution after return was pressed
            _historyCursor = 0;
            process(_buffer);
            _buffer = std::string("");
        } else if (key == SDLK_BACKSPACE && _buffer.length() > 0) {
            // Remove last character on backspace
            _buffer = _buffer.substr(0, _buffer.length() - 1);
        } else if (key == SDLK_BACKQUOTE) {
            // Deactivate console if console button was pressed
            _buffer = std::string("");
            deactivate();
        } else if (key == SDLK_UP) {
            // Move commands history up
            if (_historyCursor >= _cmdHistory.size()) {
                _historyCursor = _cmdHistory.size() - 1;
            }
            _historyCursor++;
            _buffer = _cmdHistory.at(_cmdHistory.size() - _historyCursor);
        } else if (key == SDLK_DOWN) {
            // Move commands history down
            _historyCursor--;
            if (_historyCursor < 1) {
                _historyCursor = 0;
                _buffer = "";
            } else {
                _buffer = _cmdHistory.at(_cmdHistory.size() - _historyCursor);
            }
        } 
        else if (key == SDLK_KP_PLUS || key == SDLK_KP_MINUS)
        {
            return;
        }
        updateInput();
        return;
    }
    if (key == SDLK_BACKQUOTE) {
        activate();
    }
}

void CommandInterface::handleKeyUp(SDL_Keycode key)
{
    if (_isActive)
    {
        if (key == SDLK_KP_PLUS) 
        {
            _fontSize++;
            this->loadFont(FONT_FILE, _fontSize);
            updateInput();
        }
        else if (key == SDLK_KP_MINUS)
        {
            if (_fontSize > 8)
            {
                _fontSize--;
            } 
            else 
            {
                _fontSize = 8;
            }
            this->loadFont(FONT_FILE, _fontSize);
            updateHistory();
        }
    }
}

void CommandInterface::handleText(char* characters)
{
    if (!_isActive)
        return;
    if (std::string(characters) == std::string("`"))
        return;

    _buffer.append(std::string(characters));
    updateInput();
}

void CommandInterface::subscribe(Command* commandClass)
{
    _commands.push_back(commandClass);
}

void CommandInterface::process(const std::string& command)
{
    if (command == "")
        return;

    _log->info("Processing command {0}", command);
    bool rc = false;
    for (auto it = _commands.begin(); it != _commands.end(); it++) {
        rc = (*it)->handleCommand(command);
        if (rc) {
            _log->info("Command {0} executed", command);
            splitOutput((*it)->output());
            updateHistory();
            return;
        }
    }
    if (!rc) {
        _log->warn("Command not found: {0}", command);
        _history.push_back("Command not found: " + command);
        _cmdHistory.push_back(command);
    }
    updateHistory();
}

void CommandInterface::setWidth(int w)
{
    _rect.w = w;
}

void CommandInterface::setHeight(int h)
{
    _rect.h = h;
}

void CommandInterface::splitOutput(const std::string& output)
{
    std::stringstream ss(output);
    std::string to;

    while (std::getline(ss, to, '\n')) {
        _history.push_back(to);
    }
}

void CommandInterface::drawBackground()
{
    SDL_SetRenderDrawColor(_renderer, 44, 44, 44, 200);
    SDL_RenderFillRect(_renderer, &_rect);
}

void CommandInterface::drawHistory()
{

}

void CommandInterface::addToHistory(const std::string& item)
{
    _history.push_back(item);
}
}

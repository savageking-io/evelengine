#include "Text.hpp"
#include "Engine.hpp"

namespace EvelEngine {

Text::Text(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log)
    : Object(id, manager, renderer, filename, log)
{
    _color = SDL_Color{0, 0, 0, 255};
    _size = 15;
}

Text::~Text()
{
}

void Text::setColor(SDL_Color color)
{
    _color = color;
}

void Text::setSize(int size)
{
    _size = size;
}

bool Text::load()
{
    _font = new Font(_filename, _size, _log);
    if (!_font->load()) {
        _log->error("Can't load font: {0}", _filename);
        return false;
    }
    _loaded = true;
    return true;
}

void Text::render(Camera* camera, double delta)
{
    if (!_loaded || _font == nullptr || _texture == nullptr) {
        return;
    }
    
    SDL_Rect dst = { _x, _y, _w, _h };
    SDL_RenderCopy(_renderer, _texture, NULL, &dst);
}

void Text::update()
{
    if (_font == nullptr) {
        _log->error("Can't update text: font is null");
        return;
    }
    auto surf = TTF_RenderUTF8_Solid(_font->get(), _id.c_str(), _color);
    if (surf == NULL) {
        _log->error("Failed to render `{0}`: {1}", _id, TTF_GetError());
        _texture = nullptr;
        return;
    }

    if ((_texture = SDL_CreateTextureFromSurface(_renderer, surf)) == NULL) {
        _log->error("Failed to create texture for `{0}`: {1}", _id, TTF_GetError());
        _texture = nullptr;
        return;
    }

    SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);
    SDL_FreeSurface(surf);
}

std::shared_ptr<Text> NewText(const std::string& text, const std::string& font)
{
    auto engine = Engine::get();
    auto obj = std::make_shared<Text>(text, engine->manager(), engine->renderer(), font, engine->log());
    if (!obj->load()) {
        return nullptr;
    }
    return obj;
}
}

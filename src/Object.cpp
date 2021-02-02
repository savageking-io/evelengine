#include "Object.hpp"
#include "Engine.hpp"

namespace EvelEngine {

std::shared_ptr<Object> NewObject(const std::string& id, Engine* engine, const std::string& filename)
{
    auto obj = std::make_shared<Object>(id, engine->manager(), engine->renderer(), filename, Engine::get()->log());
    if (!obj->load()) {
        return nullptr;
    }
    return obj;
}

std::shared_ptr<Object> NewObject(const std::string& id, const std::string& filename)
{
    auto obj = std::make_shared<Object>(id, Engine::get()->manager(), Engine::get()->renderer(), filename, Engine::get()->log());
    if (!obj->load()) {
        return nullptr;
    }
    return obj;
}

std::shared_ptr<Object> NewObject(const std::string& id)
{
    auto obj = std::make_shared<Object>(id, Engine::get()->manager(), Engine::get()->renderer(), Engine::get()->log());
    return obj;
}


std::shared_ptr<Object> NewObjectInQueue(const std::string& id, Engine* engine, const std::string& filename)
{
    if (engine == nullptr) {
        return nullptr;
    }
    auto obj = std::make_shared<Object>(id, engine->manager(), engine->renderer(), filename, Engine::get()->log());
    engine->addToQueue(obj);
    return obj;
}

Object::Object(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log)
    : _id(id)
    , _renderer(renderer)
    , _log(log)
    , _hidden(false)
    , _loaded(false)
    , _manager(manager)
{
    _attached = true;
    if (filename != "") {
        _log->info("Creating object with id: {0} from {1}", _id, filename);
    } else {
        _log->info("Spawning object with id: {0}", _id);
    }
    _filename = filename;
    _x = -999;
    _y = -999;
    _velocity.x = 0;
    _velocity.y = 0;
    _area = SDL_Rect{0, 0, 0, 0};
}

Object::Object(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, Log* log)
    : _id(id)
    , _renderer(renderer)
    , _log(log)
    , _hidden(false)
    , _loaded(false)
    , _manager(manager)
{
    _attached = true;
    _log->info("Spawning textureless object with id: {0}", _id);
    _filename = "";
    _x = -999;
    _y = -999;
    _velocity.x = 0;
    _velocity.y = 0;
    _area = SDL_Rect{0, 0, 0, 0};
}

Object::~Object()
{
    _log->debug("Destroying object {0}", _id);
}

bool Object::load()
{
    if (_filename == "") { return false; }
    _texture = _manager->texture(_filename);
    if (_texture == nullptr)
        return false;
    
    _log->info("Object {0} loaded", _id);
    return applyTexture(_texture);
}

bool Object::applyTexture(std::shared_ptr<Texture> texture)
{
    if (texture == nullptr)
    {
        _log->error("Failed to apply texture to {0}: texture nullptr", _id);
        return false;
    }
    if (texture->get() == nullptr)
    {
        _log->error("Underlying texture of {0} is null", _id);
        return false;
    }
    _texture = texture;
    _loaded = true;
    _log->info("Texture for object {0} applied", _id);
    setArea(0, 0, _texture->width(), _texture->height());
    return true;
}

void Object::render(Camera* camera, double delta)
{
	if (_texture == nullptr)
	{
		_log->error("NULLPTR");
	}
	if (!_loaded)
	{
		_log->error("NOT LOADED");
	}
	if (_hidden)
	{
		_log->error("HIDDEN");
	}
    if (_texture == nullptr || !_loaded || _hidden)
    {
        _log->error("SKIP {0}", _id);
        return;
    }
    SDL_Rect dst;

    int scale = 1;

    dst = { _x, _y, _aw * scale, _ah * scale };
    if (_attached) {
        dst = { _x + camera->x(), _y + camera->y(), _aw * scale, _ah * scale };
    } else {
        dst = { _x, _y, _aw * scale, _ah * scale };
    }
    SDL_RenderCopy(_renderer, _texture->get(), &_area, &dst);
    return;
}

// -

void Object::attach()
{
    _attached = true;
}

void Object::detach()
{
    _attached = false;
}

bool Object::loaded()
{
    return _loaded;
}

void Object::hide()
{
    _hidden = true;
}

void Object::show()
{
    _hidden = false;
}

// setters

void Object::setFilename(const std::string& filename)
{
    _filename = filename;
}

void Object::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

void Object::setArea(int x, int y, int w, int h)
{
    _ax = x;
    _ay = y;
    _aw = w;
    _ah = h;
    _area = {_ax, _ay, _aw, _ah};
}

void Object::setX(int x)
{
    _x = x;
}

void Object::setY(int y)
{
    _y = y;
}

void Object::setWidth(int w)
{
    _w = w;
}

void Object::setHeight(int h)
{
    _h = h;
}

// getters

int Object::x()
{
    return _x;
}

int Object::y()
{
    return _y;
}

int Object::width()
{
    return _w;
}

int Object::height()
{
    return _h;
}

const std::string& Object::id() const
{
    return _id;
}

Velocity *Object::velocity()
{
    return &_velocity;
}

int Object::getAreaHeight()
{
    return _ah;
}

int Object::getAreaWidth()
{
    return _aw;
}

int Object::getAreaX()
{
    return _ax;
}

int Object::getAreaY()
{
    return _ay;
}

}

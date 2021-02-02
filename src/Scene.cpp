#include "Scene.hpp"

namespace EvelEngine {

std::shared_ptr<Scene> NewScene(const std::string& id)
{
    auto scene = std::make_shared<Scene>(id, Engine::get()->log());
    return scene;
}

Scene::Scene(const std::string& id, Log* log)
    : _log(log)
    , _id(id)
    , _hidden(false)
{
    _log->info("Initializing new scene {0}", _id);
}

Scene::~Scene() 
{
  _log->info("Destroying scene {0}", _id);
}

void Scene::addObject(std::shared_ptr<Object> object)
{
    if (object == nullptr) {
      _log->warn("Can't add null object to the scene {0}", _id);
      return;
    }
    _log->info("Adding new object {0} to the scene {1}", object->id(), _id);
    _objects.push_back(object);
}

void Scene::addScene(std::shared_ptr<Scene> scene) {
    _scenes.push_back(std::move(scene));
}


void Scene::render(Camera *camera, double delta)
{
    if (_hidden) return;

    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        (*it)->render(camera, delta);
    }

    for (auto it = _scenes.begin(); it != _scenes.end(); it++) {
        (*it)->render(camera, delta);
    }
}

std::vector<std::shared_ptr<Object>> Scene::findObjects(int x, int y) {
    std::vector<std::shared_ptr<Object>> result;
    for (auto it = _objects.begin(); it != _objects.end(); it++) {
        int ox = (*it)->x();
        int ow = (*it)->width() + ox;
        int oy = (*it)->y();
        int oh = (*it)->height() + oy;
        if (ox <= x && ow >= x && oy <= y && oh >= y) {
            result.push_back((*it));
        } 
    }
    return result;
}

void Scene::clear()
{
    _objects.clear();
    return;
    for (auto it = _objects.begin(); it != _objects.end(); it++)
    {
        it->reset();
    }    
}

void Scene::hide()
{
    _hidden = true;
}

void Scene::show()
{
    _hidden = false;
}

bool Scene::isHidden()
{
    return _hidden;
}

std::shared_ptr<Scene> Scene::findScene(const std::string& name)
{
    for (auto it = _scenes.begin(); it != _scenes.end(); ++it)
    {
        if ((*it)->id() == name)
        {
            return (*it);
        }
    }
    return nullptr;
}

const std::string Scene::id() const
{
    return _id;
}

}

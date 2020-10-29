#include "AnimatedObject.hpp"

namespace EvelEngine {

    std::shared_ptr<AnimatedObject> NewAnimatedObject(const std::string& id, const std::string& filename)
    {
        auto obj = std::make_shared<AnimatedObject>(id, Engine::get()->manager(), Engine::get()->renderer(), filename, Engine::get()->log());
        return obj;
    }

    AnimatedObject::AnimatedObject(const std::string& id, ResourceManager* manager, SDL_Renderer* renderer, const std::string& filename, Log* log) :
        Object(id, manager, renderer, filename, log)
    {
        // During creation of an animated object we will replace _filename with the actual texture file
        // TODO: Detect file type by extension
        _frame = 0;
        _fd = 0;
        _lastTick = 0;
        _timer = new Timer(id);
        _timer->start();
    }

    AnimatedObject::~AnimatedObject()
    {

    }

    bool AnimatedObject::load()
    {
        auto af = _manager->animationFile(_filename);
        if (af == nullptr) return false;

        _frames = af->get();
        if (_frames.size() == 0 || af->texture() == "") {
            _log->error("Couldn't create animated object: Failed to load animation file");
            return false;
        }
        setFilename(af->texture());

        // Getting known frames
        _tags.clear();
        _animation = nullptr;
        auto tags = af->tags();
        for (auto &tag : tags)
        {
            if (_animation == nullptr) { _animation = &tag; }
            _tags.insert(std::make_pair(tag.tag, tag));
        }
        if (_animation == nullptr)
        {
            _log->debug("Couldn't find any animation tags");
        }

        _log->debug("Loading object from animated object for {0}", af->texture());
        return Object::load();
    }

    void AnimatedObject::render(Camera* camera, double delta)
    {
        if (_texture == nullptr || !_loaded || _hidden || _animation == nullptr)
            return;

        _lastTick = SDL_GetTicks();
        Uint32 fd = 0;
        if (_animation->frames != 0) {
            fd = (_timer->ticks() / 100) % _animation->frames;
        }

        if (_animation->start + fd > _animation->end)
        {
            _log->debug("!!!!!!!!!!!!!!!!!!!!");
            _timer->reset();
            _fd = 0;
        }

        //_log->debug("AT: {0} AS: {1} AE: {2} AF: {3}", _animation->tag, _animation->start, _animation->end, _animation->frames);
        //_log->debug("FD: {0} Frame: {1} AE: {2}", fd, _frame, _animation->end);

        SDL_Rect src;

        src = { _frames.at(_frame + fd).x, _frames.at(_frame + fd).y, _frames.at(_frame + fd).w, _frames.at(_frame + fd).h };
        SDL_Rect dst;
        if (_attached) {
            dst = { _x + camera->x(), _y + camera->y(), _frames.at(_frame).w, _frames.at(_frame).h };
        } else {
            dst = { _x, _y, _frames.at(_frame+fd).w, _frames.at(_frame+fd).h };
        }
        SDL_RenderCopy(_renderer, _texture->get(), &src, &dst);

        if (SDL_GetTicks() - _lastTick < delta) { return; }
        _lastTick = SDL_GetTicks();

        /*
           ++_frame;
           if (_animation != nullptr)
           {
           if (_frame > _animation->end)
           {
           _frame = _animation->start;
           }
           }
           else 
           {
           if (_frame > int(_frames.size() - 1)) _frame = 0;
           }
           */

        //_log->debug("Playing frame #{0}", _frame);

        return;
    }

    bool AnimatedObject::animation(const std::string& tag)
    {
        auto nt = _tags.find(tag);
        if (nt == _tags.end()) { return false; }
        _animation = &nt->second;
        _frame = _animation->start;
        _fd = 0;
        _log->debug("{0} switched animation to {1} [{2}-{3}]", _id, _animation->tag, _animation->start, _animation->end);
        return true;
    }

    const FrameRange* AnimatedObject::animation() const 
    {
        return _animation;
    }

    std::vector<FrameRange> AnimatedObject::tagsList() 
    {
        std::vector<FrameRange> tags;
        for (std::pair<std::string, FrameRange> element : _tags) {
            tags.push_back(element.second);
        }
        return tags;
    }

}

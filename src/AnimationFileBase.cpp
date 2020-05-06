#include "AnimationFileBase.hpp"

namespace EvelEngine {

    AnimationFileBase::AnimationFileBase(const std::string& filename) : _filename(std::move(filename))
    {

    }

    AnimationFileBase::~AnimationFileBase()
    {

    }

    const std::string& AnimationFileBase::filename() const 
    {
        return _filename;
    }

    const std::string& AnimationFileBase::texture() const 
    {
        return _texture;
    }

    std::vector<Frame> AnimationFileBase::get()
    {
        return _frames;
    }

    std::vector<FrameRange> AnimationFileBase::tags()
    {
        return _tags;
    }

    void AnimationFileBase::set(std::vector<Frame> frames)
    {
        _frames = frames;
    }

}

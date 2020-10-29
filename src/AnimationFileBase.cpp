#include "AnimationFileBase.hpp"

namespace EvelEngine {

    bool compare_index(const Frame &a, const Frame &b)
    {
        return a.index < b.index;
    }

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

#include "AnimationFileJSON.hpp"

namespace EvelEngine
{
    AnimationFileJSON::AnimationFileJSON(const std::string& jsonfile) : AnimationFileBase(jsonfile)
    {
        _log = Engine::get()->log();
    }

    AnimationFileJSON::~AnimationFileJSON()
    {

    }

    std::vector<Frame> AnimationFileJSON::unmarshal()
    {
        // Reset path to texture
        _texture = "";
        _frames.clear();
        _tags.clear();
        _log->info("Reading JSON animation from {0}", _filename);

        std::ifstream json(_filename);
        Json::Value root;
        json >> root;

        Json::Value meta = root["meta"];

        // load meta-data
#if EXTRACT_ANIMATION_META
        // std::string app = root["meta"].get("app", "unknown").asString();
        std::strinbg app = meta.get("app", "unknown").asString();
        std::string version = meta.get("version", "unknown").asString();
        std::string format = meta.get("format", "").asString();
#endif
        //_texture = root["meta"].get("image", "").asString();
        _texture = meta.get("image", "").asString();
        int w, h;
        w = meta["size"].get("w", 0).asInt();
        h = meta["size"].get("h", 0).asInt();
#if EXTRACT_ANIMATION_META
        _log->debug("Animation file created with: {0} [{1}]. File: {2} ({3}) {4}x{5}", app, version, _texture, format, w, h);
#else
        _log->debug("Animation File: {0} {1}x{2}", _texture, w, h);
#endif

        // Find tags
        for (Json::Value::iterator it = meta["frameTags"].begin(); it != meta["frameTags"].end(); it++)
        {
            FrameRange range;
            range.tag = (*it).get("name", "").asString();
            range.start = (*it).get("from", 0).asInt();
            range.end = (*it).get("to", 0).asInt();
            range.frames = range.end - range.start;
            range.direction = 0;
            std::string direction = (*it).get("direction", "").asString();
            if (direction == "forward")
            {
                range.direction = 1;
            }
            if (range.tag != "")
            {
                _tags.push_back(range);
            }
        }

        int i = 0;
        // load frames
        for (Json::Value::iterator it = root["frames"].begin(); it != root["frames"].end(); ++it)
        {
            Frame f;
            f.index = i;
            f.x = (*it)["frame"].get("x", 0).asInt();
            f.y = (*it)["frame"].get("y", 0).asInt();
            f.w = (*it)["frame"].get("w", 0).asInt();
            f.h = (*it)["frame"].get("h", 0).asInt();
            _log->debug("Duration {0}", (*it).get("duration", 0).asInt());
            _frames.push_back(f);
            ++i;
        }
        return _frames;
    }
    std::string AnimationFileJSON::marshal()
    {
        return "";
    }
}

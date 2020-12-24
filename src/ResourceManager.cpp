#include "ResourceManager.hpp"

#include "Poco/Path.h"

#include "Texture.hpp"
#include "AnimationFileBase.hpp"
#include "AnimationFileAseprite.hpp"
#include "AnimationFileShoeBox.hpp"
#include "Assert.hpp"

namespace EvelEngine {

    ResourceManager::ResourceManager(SDL_Renderer* renderer, FileSystem* fs, Log* log) :
        _renderer(renderer),
        _fs(fs),
        _log(log)
    {
        evel_assert(_renderer != NULL);
        evel_assert(_fs != nullptr);
        evel_assert(_log != nullptr);
        _log->info("Initializing Resource Manager");
    }

    ResourceManager::~ResourceManager()
    {

    }

    Texture* ResourceManager::texture(const std::string& id)
    {
        try {
            auto tx = _textures.at(id);
            return tx;
        } catch (std::out_of_range& ex) {
            auto tx = loadTexture(id);
            if (tx == nullptr) {
                _log->error("Can't get texture {0}", id);
            }
            return tx;
        }
    }

    std::shared_ptr<AnimationFileBase> ResourceManager::animationFile(const std::string& id)
    {
        _log->debug("Looking up animation file {0}", id);
        try {
            auto af = _animationFiles.at(id);
            _log->debug("{0} entry found", id);
            return af;
        } catch (std::out_of_range& ex) {
            _log->debug("{0} lookup failed", id);
            auto af = loadAnimationFile(id);
            if (af == nullptr) {
                _log->error("Can't get animation file {0}", id);
            }
            return af;
        }
    }

    Texture* ResourceManager::loadTexture(const std::string& path)
    {
        auto fullPath = _fs->findTexture(path);
        if (fullPath.empty())
        {
            _log->error("Texture {0} wasn't found", path);
            return nullptr;
        }

        Texture* texture = new Texture(_renderer, _log);
        if (!texture->load(fullPath)) 
        {
            _log->error("Failed to load texture from {0}", fullPath);
            return nullptr;
        }

        _textures.insert(std::pair<std::string, Texture*>(fullPath, texture));
        return texture;
    }

    std::shared_ptr<AnimationFileBase> ResourceManager::loadAnimationFile(const std::string& path)
    {
        auto fullPath = _fs->findAnimationFile(path);
        if (fullPath.empty())
        {
            _log->error("Animation file {0} wasn't found", path);
            return nullptr;
        }

        Poco::Path p(fullPath);
        _log->debug("Animation file extension: {0}", p.getExtension());
        if (p.getExtension() == "json") {
            auto af = std::make_shared<AnimationFileAseprite>(fullPath);
            af->unmarshal();
            if (af->get().size() == 0 || af->texture() == "") 
            {
                return nullptr;
            }
            _animationFiles.insert(std::pair<std::string, std::shared_ptr<AnimationFileBase> >(fullPath, af));
            return af;
        } 
        else if (p.getExtension() == "xml") {
            auto af = std::make_shared<AnimationFileShoeBox>(fullPath);
            af->unmarshal();
            if (af->get().size() == 0 || af->texture() == "") 
            {
                return nullptr;
            }
            _animationFiles.insert(std::pair<std::string, std::shared_ptr<AnimationFileBase> >(fullPath, af));
            return af;
        }

        return nullptr;   
    }

}

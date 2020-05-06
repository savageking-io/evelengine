#ifndef __EVEL_ENGINE_RESOURCE_MANAGER_HPP__
#define __EVEL_ENGINE_RESOURCE_MANAGER_HPP__

#include <map>

#include "Font.hpp"
#include "Log.hpp"
#include "FileSystem.hpp"

namespace EvelEngine {

    class Texture;
    class AnimationFileBase;
    class AnimationFileJSON;
    
    class ResourceManager {
        public:
            ResourceManager(SDL_Renderer* renderer, FileSystem* fs, Log* log);
            ~ResourceManager();
            Texture* texture(const std::string& id);
            std::shared_ptr<AnimationFileBase> animationFile(const std::string& id);
        private:
            Texture* loadTexture(const std::string& path);
            std::shared_ptr<AnimationFileBase> loadAnimationFile(const std::string& path);
            SDL_Renderer* _renderer;
            FileSystem* _fs;
            Log* _log;
            std::map<std::string, Texture*> _textures;
            std::map<std::string, std::shared_ptr<AnimationFileBase> > _animationFiles;
    };
};

#endif

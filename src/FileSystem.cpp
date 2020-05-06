#include "FileSystem.hpp"
#include "Assert.hpp"
#include "Engine.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#else
#include <sys/stat.h>
#endif

namespace EvelEngine {

    FileSystem::FileSystem(const std::string& root, Log* log) : 
        _log(log),
        _root(root)
        {
            if (_root.empty()) _root = ".";
            appendSlash();
            if (_log) _log->info("Initializing File System at {0}", _root);
        }

    FileSystem::~FileSystem()
    {

    }

    const std::string& FileSystem::root() const 
    {
        return _root;
    }

    void FileSystem::root(const std::string& root)
    {
        _root = root;
        appendSlash();
    }

    bool FileSystem::exists(const std::string& path) const
    {
#if defined(__EVEL_UNIX)
        struct stat st;
        auto np = _root + path;
        return stat(np.c_str(), &st) == 0;
#else
#error "Not implemented"
#endif
    }

    bool FileSystem::addTexturesPath(const std::string& path)
    {
        if (!exists(path)) 
        {
            if (_log) _log->error("Can't add path to textures: Directory doesn't exists");
            return false;
        }

        for (auto &p : _texturesDirectories)
        {
            if (p == path)
            {
                if (_log) _log->error("Can't add path to textures: Already in list");
                return false;
            }
        }
        _texturesDirectories.push_back(path);
        return true;
    }

    bool FileSystem::addAnimationFilesPath(const std::string& path)
    {
        if (!exists(path)) 
        {
            if (_log) _log->error("Can't add path to animation files: Directory doesn't exists");
            return false;
        }

        for (auto &p : _animationFilesDirectories)
        {
            if (p == path)
            {
                if (_log) _log->error("Can't add path to animation files: Already in list");
                return false;
            }
        }
        _animationFilesDirectories.push_back(path);
        return true;
    }

    std::vector<std::string> FileSystem::texturePath()
    {
        return _texturesDirectories;
    }

    std::vector<std::string> FileSystem::animationFilesPath()
    {
        return _animationFilesDirectories;
    }

    std::string FileSystem::findTexture(const std::string& path) const
    {
        // Try texture by full path
        if (exists(path)) {
            _log->debug("Texture {0} found by specified path", path);
            return (_root + path);
        }
        for (auto &p : _texturesDirectories)
        {
            _log->debug("Searching for texture {0} in {1}", path, (_root + p));
            if (exists(p + path)) return (_root + p + path);
        }

        _log->debug("Texture {0} not found", path);
        return "";
    }

    std::string FileSystem::findAnimationFile(const std::string& path) const
    {
        // Try texture by full path
        if (exists(path)) {
            _log->debug("Animation file {0} found by specified path", path);
            return (_root + path);
        }
        for (auto &p : _animationFilesDirectories)
        {
            _log->debug("Searching for animation file {0} in {1}", path, (_root + p));
            if (exists(p + path)) return (_root + p + path);
        }

        _log->debug("Animation file {0} not found", path);
        return "";
    }

    std::vector<std::byte> FileSystem::read(const std::string& filename)
    {
        return std::vector<std::byte>();
    }

    void FileSystem::appendSlash()
    {
#if defined(__EVEL_WIN)

#elif defined(__EVEL_UNIX)
        if (_root.substr(_root.length() - 1) != "/")
        {
            _root.append("/");
        }
#else
#error "Not implemented"
#endif
    }
}

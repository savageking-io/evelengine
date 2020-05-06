#ifndef __EVEL_ENGINE_FILESYSTEM_HPP__
#define __EVEL_ENGINE_FILESYSTEM_HPP__

#include <string>
#include <vector>

#include "Log.hpp"

namespace EvelEngine {

    ///
    /// \class FileSystem
    /// \brief File system related methods
    ///
    /// This class is intended to provide OS-specific file system functions
    /// like dealing with path, files and directories
    class FileSystem
    {
        public:
            //! Constructor
            /*!
             * Initialize FileSystem class with the path to root directory
             *
             * Root directory is a top-level directory for searching for files
             * and directories. All the path used by the application will be
             * considered relative to this path
             *
             * \param root - path to top-level directory
             * \param log - reference to Log
             */
            FileSystem(const std::string& root, Log* log);

            //! Destructor
            ~FileSystem();

            //! Return top-level directory
            /*!
             * \return top-level directory
             */
            const std::string& root() const;

            //! Set new top-level directory
            /*!
             * Set new top level directory for the FileSystem
             * \param path to new top-level directory
             */
            void root(const std::string& root);

            //! Whether file or directory exists or not
            /*!
             * This method checks if file or directory exists. 
             *
             * \param path
             * \return bool
             */
            bool exists(const std::string& path) const;

            //! Adds texture lookup path
            /*!
             * Adds a new path for texture lookup.
             * Path should be relative to _root
             *
             * \param path to a directory with textures
             * \return false if new path doesn't exists, true otherwise
             */
            bool addTexturesPath(const std::string& path);

            //! Adds animation files lookup path
            /*!
             * Adds a new path for animation definition files lookup.
             * Path should be relative to _root
             *
             * \param path to a directory with animation data files
             * \return false if new path doesn't exists, true othewise
             */
            bool addAnimationFilesPath(const std::string& path);
            
            //! Return vector of path to textures
            /*!
             * \return vector of path to textures
             */
            std::vector<std::string> texturePath();

            //! Return vector of path to animation files
            /*!
             * \return vector of path to animation files 
             */
            std::vector<std::string> animationFilesPath();

            //! Find texture with specified path in all known directories
            /*!
             * This method will go through all known texture directories (if any)
             * and look for a file provided by path. If file found, returns
             * full path. Empty string otherwise
             * 
             * \param path
             * \return full path to resource
             */
            std::string findTexture(const std::string& path) const;

            std::vector<std::byte> read(const std::string& filename);

            //! Find animation file with specified path in all known directories
            /*!
             * This method will go through all known animation file directories (if any)
             * and look for a file provided by path. If file found, returns
             * full path. Empty string otherwise
             * 
             * \param path
             * \return full path to resource
             */
            std::string findAnimationFile(const std::string& path) const;

            //! Whether current path is absolute
            bool isAbsolute();
        private:
            //! Append slash (or backslash) to the end of root directory
            void appendSlash();

        private:
            Log* _log;                                              ///< Reference to Log Subsystem
            std::string _root;                                      ///< Path to top-level directory
            std::string _absoluteRoot;                              ///< Absolute path to top-level directory
            std::vector<std::string> _texturesDirectories;          ///< Path to textures directories
            std::vector<std::string> _animationFilesDirectories;    ///< Path to animation files directories
    };

}

#endif

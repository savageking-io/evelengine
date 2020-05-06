#ifndef __EVEL_ENGINE_TILESET_HPP__
#define __EVEL_ENGINE_TILESET_HPP__

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace EvelEngine {
    ///
    /// \class Tileset
    /// \brief Load and parse tileset images from text files or from image automatically
    ///
    class Tileset {
        public:
            //! Default Constructor
            /**
             * Constructor initializes logging subsystem and Simulation
             *
             */
            Tileset();
            //! Constructor
            /**
             * When this constructor is called, system will try to load text
             * file that defines tileset configuration and have path to actual 
             * tileset image. 
             * If file specified is an image, system will try to automatically 
             * determine tiles by taking first pixel of it and presume, that this
             * pixel is of background color. 
             *
             * \param filepath - path to tileset definition or image
             */
            Tileset(const std::string& filepath);
            Tileset(const std::string& filepath, const std::string& bgcolor);
            Tileset(const std::string& filepath, int sx, int sy);
            Tileset(const std::string& filepath, int sx, int sy, int ox, int oy);
            ~Tileset();
        private:
            std::shared_ptr<spdlog::logger> _log; ///< Logging subsystem
    };

    std::shared_ptr<Tileset> NewTileset();
    std::shared_ptr<Tileset> NewTileset(const std::string& filepath);
    std::shared_ptr<Tileset> NewTileset(const std::string& filepath, const std::string& bgcolor);
    std::shared_ptr<Tileset> NewTileset(const std::string& filepath, int sx, int sy);
    std::shared_ptr<Tileset> NewTileset(const std::string& filepath, int sx, int sy, int ox, int oy);
}

#endif

#ifndef __EVEL_ENGINE_TILESETBASE_HPP__
#define __EVEL_ENGINE_TILESETBASE_HPP__

#include <string>

#include "Log.hpp" 

namespace EvelEngine {

    struct Tileset 
    {
        int Width;
        int Height;
        int Margin;
        int Spacing;
        int Columns;
        int Size;
        int TileWidth;
        int TileHeight;
        std::string Name;
        std::string Image;
    };

    ///
    /// \class TilesetBase
    /// \brief Load and parse TilesetBase images from text files or from image automatically
    ///
    class TilesetBase {
        public:
            //! Default Constructor
            /**
             * Constructor initializes logging subsystem and Simulation
             *
             */
            TilesetBase();
            //! Constructor
            /**
             * When this constructor is called, system will try to load text
             * file that defines TilesetBase configuration and have path to actual 
             * TilesetBase image. 
             * If file specified is an image, system will try to automatically 
             * determine tiles by taking first pixel of it and presume, that this
             * pixel is of background color. 
             *
             * \param filepath - path to TilesetBase definition or image
             */
            TilesetBase(const std::string& filepath);
            TilesetBase(const std::string& filepath, const std::string& bgcolor);
            TilesetBase(const std::string& filepath, int sx, int sy);
            TilesetBase(const std::string& filepath, int sx, int sy, int ox, int oy);
            ~TilesetBase();
        protected:
            std::string _filepath;
            Log* _log; ///< Logging subsystem
        private:
    };
}

#endif

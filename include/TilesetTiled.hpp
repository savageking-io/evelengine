#ifndef __TILESET_TILED_HPP__
#define __TILESET_TILED_HPP__

#include "TilesetBase.hpp"

namespace EvelEngine {
    class TilesetTiled : public TilesetBase 
    {
        public:
            TilesetTiled(const std::string& filepath);
            ~TilesetTiled();
            bool load();
            Tileset* tileset();
        private:
            Tileset _tileset;
    };

    std::shared_ptr<TilesetTiled> NewTilesetTiled(const std::string& filepath);
}

#endif 
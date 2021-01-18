#include "TilesetBase.hpp"

#include "Engine.hpp"

namespace EvelEngine {

    TilesetBase::TilesetBase() 
    {
        
    }

    TilesetBase::TilesetBase(const std::string& filepath) : _filepath(filepath) {
        _log = Engine::get()->log();
    }

    TilesetBase::TilesetBase(const std::string& filepath, const std::string& bgcolor)
    {

    }
    TilesetBase::TilesetBase(const std::string& filepath, int sx, int sy) 
    {

    }

    TilesetBase::TilesetBase(const std::string& filepath, int sx, int sy, int ox, int oy)
    {

    }

    TilesetBase::~TilesetBase() 
    {

    }
}

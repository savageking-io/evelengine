#include "TilesetTiled.hpp"

#include <fstream>

#include "json/json.h"

namespace EvelEngine {

    TilesetTiled::TilesetTiled(const std::string& filepath) : TilesetBase(filepath) 
    {

    }

    TilesetTiled::~TilesetTiled()
    {

    }

    bool TilesetTiled::load()
    {
        _log->debug("Reading Tiled's tileset from {0}", _filepath);

        std::ifstream json(_filepath);
        Json::Value root;
        json >> root;

        _tileset.Columns = root["columns"].asInt();
        _tileset.Height = root["imageheight"].asInt();
        _tileset.Image = root["image"].asString();
        _tileset.Margin = root["margin"].asInt();
        _tileset.Name = root["name"].asString();
        _tileset.Size = root["tilecount"].asInt();
        _tileset.Spacing = root["spacing"].asInt();
        _tileset.TileHeight = root["tileheight"].asInt();
        _tileset.TileWidth = root["tilewidth"].asInt();
        _tileset.Width = root["imagewidth"].asInt();

        _log->debug("Tileset name: {0}", _tileset.Name);

        return true;
    }

    Tileset* TilesetTiled::tileset()
    {
        return &_tileset;
    }

    std::shared_ptr<TilesetTiled> NewTilesetTiled(const std::string& filepath)
    {
        auto obj = std::make_shared<TilesetTiled>(filepath);
        if (!obj->load()) {
            return nullptr;
        }
        return obj;
    }
}
#include "World.hpp"

#include "PerlinNoise.hpp"

World::World(Player* p) : _p(p)
{
    _log = EvelEngine::Engine::get()->log();
}

World::~World()
{

}

void World::generate()
{
    _log->info("Beginning World Generation");
    if (_p == nullptr) 
    {
        _log->error("player nullptr");
        return;
    }

    // Determine chunk where player resides
    int startChunkX = _p->x() / CHUNK_SIZE;
    int startChunkY = _p->y() / CHUNK_SIZE;
    _log->info("Start chunk: {0} {1}", startChunkX, startChunkY);
    
    int half = CHUNK_RENDER_DISTANCE / 2 + 1;

    // start chunk x, y is now a center of the world
    // we generate chunks around it 
    for (int x = startChunkX - half; x < startChunkX + half; x++)
    {
        for (int y = startChunkY - half; y < startChunkY + half; y++)
        {
            _log->info("Creating chunk {0} {1}", x, y);
            Chunk c(x, y);
            _chunks.push_back(c);
        }
    }
}

void World::generate_water()
{
    
}

#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#define CHUNK_SIZE 16
// Must be odd number
#define CHUNK_RENDER_DISTANCE 17

#include <vector>
typedef enum {
    grass0,
    grass1,
    soil0,
    water0
} BlockType;

struct Block {
    int x;
    int y;

};

class Chunk
{
    public:
        Chunk(int x, int y);
        ~Chunk();
        int x;
        int y;
    private:
        std::vector<Block> _blocks;
};

#endif

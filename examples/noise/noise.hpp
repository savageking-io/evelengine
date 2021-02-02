#ifndef __NOISE_HPP__
#define __NOISE_HPP__

#include "PerlinNoise.hpp"
#include "Texture.hpp"

struct NoiseParams {
    double freq;
    int octaves;
    double offset;
    uint32_t seed;
};

class NoiseExample
{
    public:
        NoiseExample(NoiseParams* params);
        ~NoiseExample();
        void generate(std::shared_ptr<EvelEngine::Texture> texture);
        void clear();
        NoiseParams* params();
    private:
        NoiseParams* _params;
};


#endif

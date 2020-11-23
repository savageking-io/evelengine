#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "AnimatedObject.hpp"
#include "Point.hpp"
#include "NoiseConsole.hpp"

#include "noise.hpp"

#include "Poco/Random.h"

#define SCREEN_W 720
#define SCREEN_H 480

NoiseExample::NoiseExample(NoiseParams* params) : _params(params)
{
    _params->octaves = 8;
    _params->offset = 1.0;    
    _params->freq = 8.0;
}

NoiseExample::~NoiseExample()
{

}

void NoiseExample::generate()
{
    const siv::PerlinNoise perlin(_params->seed);
    const double fx = SCREEN_W / _params->freq;
    const double fy = SCREEN_H / _params->freq;

    const int m = 100;

    // Ridged
    double weight = 1.0;

    for (int x = 0; x < SCREEN_W; ++x)
    {
        for (int y = 0; y < SCREEN_H; ++y)
        {
            double p = perlin.accumulatedOctaveNoise2D_0_1(x / fx, y /fy, _params->octaves);
            auto v = (p >= 1.0 ? 255 : (p <= 0.0 ? 0 : (int)floor(p * 256.0)));

            // Ridged
            v = abs(v);
            v = _params->offset - v;

            v *= v;
            // v *= weight;

            SDL_Color c;
            c.r = c.g = c.b = Uint8(v);
            c.a = 255;
            auto point = EvelEngine::NewPoint("point", x, y, c);
            EvelEngine::Engine::get()->scene()->addObject(point);
        }
    }
}

void NoiseExample::clear()
{
    EvelEngine::Engine::get()->scene()->clear();
}

NoiseParams* NoiseExample::params()
{
    return _params;
}

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();
    auto log = engine->log();

    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);

    engine->initialize();

    auto cmd = new CommonConsole();
    engine->cli()->subscribe(cmd);

    Poco::Random rnd;
    rnd.seed();

    NoiseParams p;
    p.seed = rnd.next(500);

    NoiseExample n(&p);

    auto noiseCmd = new NoiseConsole(&n);
    engine->cli()->subscribe(noiseCmd);

    // Initial generation
    n.generate();


    return engine->run();
}

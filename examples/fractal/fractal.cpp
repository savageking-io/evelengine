#include <complex>

#include "Engine.hpp"
#include "Scene.hpp"
#include "Point.hpp"

#define SCREEN_W 600 
#define SCREEN_H 600 

int value(int x, int y)  {
    std::complex<float> point((float)x/SCREEN_W-1.5, (float)y/SCREEN_H-0.5);
    std::complex<float> z(0, 0);
    unsigned int nb_iter = 0;
    while (abs(z) < 2 && nb_iter <= 34) {
        z = z * z + point;
        nb_iter++;
    }
    if (nb_iter < 34) return (255*nb_iter)/33;
    else return 0;
}

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();        
    auto log = engine->log();
    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);
    engine->initialize();
    auto renderer = engine->renderer();

    for (int y = 1; y <= SCREEN_H; ++y)
    {
        for (int x = 1; x <= SCREEN_W; ++x)
        {
            Uint8 color = value(x, y);
            if (color == 0) continue;
            auto p = EvelEngine::NewPoint("1", x, y, SDL_Color{color, 0, 0, 0}); 
            engine->scene()->addObject(p);
        }
    }

    return engine->run();
}

#include "Engine.hpp"
#include "Scene.hpp"
#include "Point.hpp"

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();        
    auto log = engine->log();
    engine->setWindowWidth(480);
    engine->setWindowHeight(320);
    engine->initialize();
    auto renderer = engine->renderer();

    Uint8 r = 0, g = 0, b = 0;
    for (int x = 0; x < 480; x = x + 4)
    {
        for (int y = 0; y < 320; y = y + 4)
        {
            auto p = EvelEngine::NewPoint("1", x, y, SDL_Color{r, g, b, 0});
            if (!p) 
            {
                log->error("Point creation failed");
                continue;
            }
            engine->scene()->addObject(p);
            ++r;
            if (r > 255) {
                r = 0;
                g++;
            }
        }
    }

    return engine->run();
}

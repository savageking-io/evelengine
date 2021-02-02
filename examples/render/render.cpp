#include <sstream>

#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "Object.hpp"

#include "Poco/Random.h"

#define SCREEN_W 720
#define SCREEN_H 480
#define SEED 16
#define TEXTURE "assets/sprites/green-box.png"

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();

    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);

    engine->initialize();

    auto cmd = new CommonConsole();
    engine->cli()->subscribe(cmd);

    auto texture = engine->manager()->texture(TEXTURE);
    if (texture == nullptr)
    {
        engine->log()->error("Couldn't load texture");
        return 1;
    }

    Poco::Random r;
    r.seed(SEED);

    for (int i = 0; i < 200; i++)
    {
        std::stringstream name;
        name << "box_" << i;
        auto o = EvelEngine::NewObject(name.str());
        //o->load();
        
        int x = r.next(SCREEN_W);
        int y = r.next(SCREEN_H);
        o->setPosition(x, y);
        o->applyTexture(texture);
        engine->scene()->addObject(o);
    }
    
    return engine->run();
}

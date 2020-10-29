#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "AnimatedObject.hpp"

#define SCREEN_W 720
#define SCREEN_H 480

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();
    // auto log = engine->log();

    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);

    engine->initialize();

    auto cmd = new CommonConsole();
    engine->cli()->subscribe(cmd);

    auto priestess = EvelEngine::NewAnimatedObject("priestess", "assets/sprites/priestess.json");
    priestess->load();
    priestess->animation("walk_s");
    priestess->setPosition(100, 100);

    engine->scene()->addObject(priestess);

    return engine->run();
}

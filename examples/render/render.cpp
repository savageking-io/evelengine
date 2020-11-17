#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "Object.hpp"

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

    auto box = EvelEngine::NewObject("green-box", "assets/sprites/green-box.png");
    box->setPosition(0, 0);

    engine->scene()->addObject(box);

    return engine->run();
}

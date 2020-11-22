#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "Object.hpp"

#include "Player.hpp"
#include "Chunk.hpp"
#include "World.hpp"

#define SCREEN_W 720
#define SCREEN_H 480

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();

    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);

    engine->initialize();

    auto cmd = new CommonConsole();
    engine->cli()->subscribe(cmd);

    Player p(1024, 1024);

    World w(&p);
    w.generate();

    return engine->run();
}

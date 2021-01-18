#include "Engine.hpp"

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();

    return engine->run();
}
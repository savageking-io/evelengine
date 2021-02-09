#include <sstream>

#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "Object.hpp"
#include "Texture.hpp"

#include "Poco/Random.h"

#define SCREEN_W 720
#define SCREEN_H 480
#define SEED 16
#define TEXTURE "assets/sprites/green-box.png"
#define TEXTURE2 "assets/sprites/smile.png"
#define SPRITE_SIZE 64

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

    auto texture2 = engine->manager()->texture(TEXTURE2);
    if (texture2 == nullptr)
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

    auto new_texture = EvelEngine::NewTexture("new_texture");
    new_texture->createBlank("new_texture", SPRITE_SIZE * 3, SPRITE_SIZE);

    std::vector<std::shared_ptr<EvelEngine::Texture> > textures;

    // Attempt to create a texture
    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "s_" << i;
        auto o = EvelEngine::NewObject(name.str(), TEXTURE2);
        o->load();
        o->setPosition(0, 0);
        
        auto txt = o->draw();
        txt->source(0, 0, SPRITE_SIZE, SPRITE_SIZE);
        txt->destination(i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE);
        textures.push_back(txt);
    }

    new_texture->draw(textures);
    textures.clear();

    auto obj = EvelEngine::NewObject("3smiles");
    obj->setPosition(100, 100);
    obj->applyTexture(new_texture);
    engine->scene()->addObject(obj);
    
    return engine->run();
}

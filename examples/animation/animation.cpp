#include <sstream>
#include "Poco/Random.h"

#include "Engine.hpp"
#include "Scene.hpp"
#include "CommonConsole.hpp"
#include "AnimatedObject.hpp"
#include "Text.hpp"

#include <map>

#define SCREEN_W 1024
#define SCREEN_H 768
#define FONT "assets/kenney_fontpackage/Fonts/Kenney Pixel.ttf"

int main(int argc, char* argv[])
{
    auto engine = EvelEngine::Engine::get();
    auto log = engine->log();

    engine->setWindowWidth(SCREEN_W);
    engine->setWindowHeight(SCREEN_H);

    engine->initialize();

    auto cmd = new CommonConsole();
    engine->cli()->subscribe(cmd);

    const std::map<int, std::string> animationFiles = {
        {0, "assets/kenney_tooncharacters1/Female adventurer/Tilesheet/character_femaleAdventurer_sheet.xml"},
        {1, "assets/kenney_tooncharacters1/Female person/Tilesheet/character_femalePerson_sheet.xml"},
        {2, "assets/kenney_tooncharacters1/Male adventurer/Tilesheet/character_maleAdventurer_sheet.xml"},
        {3, "assets/kenney_tooncharacters1/Male person/Tilesheet/character_malePerson_sheet.xml"},
        {4, "assets/kenney_tooncharacters1/Robot/Tilesheet/character_robot_sheet.xml"},
        {5, "assets/kenney_tooncharacters1/Zombie/Tilesheet/character_zombie_sheet.xml"},
    };

    for (int i = 0; i <= 5; i++)
    {
        auto obj = EvelEngine::NewAnimatedObject("", animationFiles.at(i));
        obj->load();
        auto tags = obj->tagsList();

        Poco::Random rnd;
        rnd.seed();
        int index = rnd.next(tags.size());

        auto tag = tags.at(index);

        obj->animation(tag.tag);
        obj->setPosition(i * 140, 400);

        auto animation_name = EvelEngine::NewText(tag.tag, FONT);
        animation_name->setSize(30);
        animation_name->load();
        animation_name->setColor(SDL_Color{255, 255, 255, 255});
        animation_name->update();
        animation_name->setPosition(i * 140, 550);

        std::stringstream frames;
        frames << int(tag.start) << " - " << int(tag.end);

        log->info("Frames: {0}. Tag: {1}-{2}", frames.str(), tag.start, tag.end);

        auto animation_frames = EvelEngine::NewText(frames.str(), FONT);
        animation_frames->setSize(30);
        animation_frames->load();
        animation_frames->setColor(SDL_Color{255, 255, 255, 255});
        animation_frames->update();
        animation_frames->setPosition(i * 140, 580);

        engine->scene()->addObject(obj);
        engine->scene()->addObject(animation_name);
        engine->scene()->addObject(animation_frames);
    }

    return engine->run();
}

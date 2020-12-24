# evelengine
2D Game Engine [SDL, C++]

This projects is WIP, so don't expect anything

# Building
This project uses `conan` for dependency management. Refer to their [website](https://conan.io) for installation instructions and usage guides. 

### Linux
```
conan install ./.conanfile --build fmt --build gtest --build jsoncpp --build spdlog --build yaml-cpp -s compiler.libcxx=libstdc++11
./configure
make
make install
```

### Windows
In Visual Studio Code select Extensions, search for `conan` and install it [Read more about extensions](https://docs.conan.io/en/latest/integrations/ide/visual_studio.html).


# Additional files
If you wish to run examples and tests you need a [Minecraft Font by Pwnage Block](https://www.deviantart.com/pwnage-block/art/Minecraft-Font-194517479)

For examples and tests to work properly you need to download and unpack different assets from [Kenney's Website](https://kenney.nl). Also consider supporting his work on Patreon, because he makes a valuable contribution in Game Development in general and Indie Dev in particular. Here is a list of assets required:

* [Kenney Fonts](https://kenney.nl/assets/kenney-fonts)
* [Toon Characters 1](https://kenney.nl/assets/toon-characters-1) - Used in `animation` example

Move downloaded ZIP files to `assets/` directory and extract them there.
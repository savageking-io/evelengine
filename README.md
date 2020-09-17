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

# Additional files
If you wish to run examples you need a [Minecraft Font by Pwnage Block](https://www.deviantart.com/pwnage-block/art/Minecraft-Font-194517479)


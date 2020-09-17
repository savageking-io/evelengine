include conanbuildinfo.mak

#export CC=g++
export CXXFLAGS=-DSPDLOG_FMT_EXTERNAL -g -I $(CURDIR)/include \
	-I$(CONAN_ROOT_SPDLOG)/include \
	-I$(CONAN_ROOT_FMT)/include \
	-I$(CONAN_ROOT_JSONCPP)/include \
	-I$(CONAN_ROOT_YAMLCPP)/include \
	-I$(CONAN_ROOT_POCO)/include \
	-std=c++17 -Wall
export LDFLAGS=-g -L$(CONAN_ROOT_JSONCPP)/lib -L$(CONAN_ROOT_FMT)/lib -L$(CONAN_ROOT_SPDLOG)/lib -L$(CONAN_ROOT_YAMLCPP)/lib -L$(CONAN_ROOT_POCO)/lib $(SDL_LIBS) 
#export LDFLAGS=-g -L$(CONAN_ROOT_JSONCPP)/lib -L$(CONAN_ROOT_FMT)/lib -L$(CONAN_ROOT_SPDLOG)/lib -lfmt -lspdlog $(SDL_LIBS) -ljsoncpp
export BINARY=libevelengine
export LIB_DIRECTORY=$(CURDIR)/lib
# Top directory for example projects
export APP_DIRECTORY=examples
export BIN_DIRECTORY=$(CURDIR)/bin
export BUILD_DIRECTORY=$(CURDIR)/build
export DIST_DIRECTORY=$(CURDIR)/dist
SOURCE_DIR=src
INCLUDE_DIR=include
CONFIGFILE=make.config

OBJECT_FILES =  $(BUILD_DIRECTORY)/Engine.o \
		$(BUILD_DIRECTORY)/Assert.o \
		$(BUILD_DIRECTORY)/Log.o \
		$(BUILD_DIRECTORY)/ConfigurationBase.o \
		$(BUILD_DIRECTORY)/ConfigurationYAML.o \
		$(BUILD_DIRECTORY)/FileSystem.o \
		$(BUILD_DIRECTORY)/Timer.o \
		$(BUILD_DIRECTORY)/Scene.o \
		$(BUILD_DIRECTORY)/Object.o \
		$(BUILD_DIRECTORY)/Tileset.o \
		$(BUILD_DIRECTORY)/AnimationFileBase.o \
		$(BUILD_DIRECTORY)/AnimationFileJSON.o \
		$(BUILD_DIRECTORY)/AnimatedObject.o \
		$(BUILD_DIRECTORY)/Level.o \
		$(BUILD_DIRECTORY)/Texture.o \
		$(BUILD_DIRECTORY)/Font.o \
		$(BUILD_DIRECTORY)/Event.o \
		$(BUILD_DIRECTORY)/EventBase.o \
		$(BUILD_DIRECTORY)/Simulation.o \
		$(BUILD_DIRECTORY)/Stats.o \
		$(BUILD_DIRECTORY)/CommandInterface.o \
		$(BUILD_DIRECTORY)/Command.o \
		$(BUILD_DIRECTORY)/Seed.o \
		$(BUILD_DIRECTORY)/Camera.o \
		$(BUILD_DIRECTORY)/ResourceManager.o \
		$(BUILD_DIRECTORY)/Primitives.o \
		$(BUILD_DIRECTORY)/Point.o \
		$(BUILD_DIRECTORY)/Rectangle.o \
		$(BUILD_DIRECTORY)/StringsUtil.o \
		$(BUILD_DIRECTORY)/Text.o \
		$(BUILD_DIRECTORY)/RuntimeStats.o

include $(CONFIGFILE)

all: lib examples tests

lib: static shared

shared: directories
shared: $(LIB_DIRECTORY)/$(BINARY).$(EXT)

static: directories
static: $(LIB_DIRECTORY)/$(BINARY).a


doc:
	doxygen docs/Doxyfile

tests: lib
	$(MAKE) -C ./testsuite suite

assets: examples
	$(MAKE) -C ./templates generate

test: tests
	@LD_LIBRARY_PATH=./lib bin/testsuite

directories:
	@mkdir -p $(LIB_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)
	@mkdir -p $(DIST_DIRECTORY)

archive: lib
	tar zcvf $(DIST_DIRECTORY)/$(ARCHIVE) lib/*a lib/*.$(EXT)

clean: examples-clean
	$(MAKE) -C ./testsuite clean
	-rm -rf docs/out
	-rm -f $(LIB_DIRECTORY)/$(BINARY)*
	-rm -f $(OBJECT_FILES)

distclean: clean examples-distclean
	$(MAKE) -C ./testsuite distclean
	-rm -f $(CONFIGFILE)
	-rm -f make.examples
	-rm -rf $(LIB_DIRECTORY)
	-rm -rf $(BIN_DIRECTORY)
	-rm -rf $(BUILD_DIRECTORY)
	-rm -rf $(EXAMPLES_DIRECTORY)

install:
	cp $(LIB_DIRECTORY)/libevelengine* $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/evelengine
	cp $(CURDIR)/include/*.hpp $(PREFIX)/include/evelengine/

uninstall:
	rm -f $(PREFIX)/lib/libevelengine*
	rm -rf $(PREFIX)/include/evelengine

$(BUILD_DIRECTORY)/Engine.o: $(SOURCE_DIR)/Engine.cpp $(INCLUDE_DIR)/Engine.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Assert.o: $(SOURCE_DIR)/Assert.cpp $(INCLUDE_DIR)/Assert.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Log.o: $(SOURCE_DIR)/Log.cpp $(INCLUDE_DIR)/Log.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/ConfigurationBase.o: $(SOURCE_DIR)/ConfigurationBase.cpp $(INCLUDE_DIR)/ConfigurationBase.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/ConfigurationYAML.o: $(SOURCE_DIR)/ConfigurationYAML.cpp $(INCLUDE_DIR)/ConfigurationYAML.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/FileSystem.o: $(SOURCE_DIR)/FileSystem.cpp $(INCLUDE_DIR)/FileSystem.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Timer.o: $(SOURCE_DIR)/Timer.cpp $(INCLUDE_DIR)/Timer.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Exception.o: $(SOURCE_DIR)/Exception.cpp $(INCLUDE_DIR)/Exception.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/StringsUtil.o: $(SOURCE_DIR)/StringsUtil.cpp $(INCLUDE_DIR)/StringsUtil.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Scene.o: $(SOURCE_DIR)/Scene.cpp $(INCLUDE_DIR)/Scene.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Object.o: $(SOURCE_DIR)/Object.cpp $(INCLUDE_DIR)/Object.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Tileset.o: $(SOURCE_DIR)/Tileset.cpp $(INCLUDE_DIR)/Tileset.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/AnimationFileBase.o: $(SOURCE_DIR)/AnimationFileBase.cpp $(INCLUDE_DIR)/AnimationFileBase.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/AnimationFileJSON.o: $(SOURCE_DIR)/AnimationFileJSON.cpp $(INCLUDE_DIR)/AnimationFileJSON.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/AnimatedObject.o: $(SOURCE_DIR)/AnimatedObject.cpp $(INCLUDE_DIR)/AnimatedObject.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Level.o: $(SOURCE_DIR)/Level.cpp $(INCLUDE_DIR)/Level.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Texture.o: $(SOURCE_DIR)/Texture.cpp $(INCLUDE_DIR)/Texture.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Font.o: $(SOURCE_DIR)/Font.cpp $(INCLUDE_DIR)/Font.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/CommandInterface.o: $(SOURCE_DIR)/CommandInterface.cpp $(INCLUDE_DIR)/CommandInterface.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Command.o: $(SOURCE_DIR)/Command.cpp $(INCLUDE_DIR)/Command.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Event.o: $(SOURCE_DIR)/Event.cpp $(INCLUDE_DIR)/Event.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/EventBase.o: $(SOURCE_DIR)/EventBase.cpp $(INCLUDE_DIR)/EventBase.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Simulation.o: $(SOURCE_DIR)/Simulation.cpp $(INCLUDE_DIR)/Simulation.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Stats.o: $(SOURCE_DIR)/Stats.cpp $(INCLUDE_DIR)/Stats.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Seed.o: $(SOURCE_DIR)/Seed.cpp $(INCLUDE_DIR)/Seed.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Camera.o: $(SOURCE_DIR)/Camera.cpp $(INCLUDE_DIR)/Camera.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/ResourceManager.o: $(SOURCE_DIR)/ResourceManager.cpp $(INCLUDE_DIR)/ResourceManager.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Primitives.o: $(SOURCE_DIR)/Primitives.cpp $(INCLUDE_DIR)/Primitives.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Rectangle.o: $(SOURCE_DIR)/Rectangle.cpp $(INCLUDE_DIR)/Rectangle.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Point.o: $(SOURCE_DIR)/Point.cpp $(INCLUDE_DIR)/Point.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/Text.o: $(SOURCE_DIR)/Text.cpp $(INCLUDE_DIR)/Text.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(BUILD_DIRECTORY)/RuntimeStats.o: $(SOURCE_DIR)/RuntimeStats.cpp $(INCLUDE_DIR)/RuntimeStats.hpp
	$(CXX) $(CXXFLAGS) -c -fPIC $< -o $@

$(LIB_DIRECTORY)/$(BINARY).$(EXT): $(OBJECT_FILES) 
	$(CXX) $(OBJECT_FILES) $(LDFLAGS) -shared -o $@

$(LIB_DIRECTORY)/$(BINARY).a: $(OBJECT_FILES)
	$(AR) $(ARFLAGS) $@ $^

make.examples:
	$(error Missing make.examples file. Run configure script first)

make.config:
	$(error Missing make.config file. Run configure script first)

# Examples
examples: dot fractal

dot: 
	$(MAKE) -C ./examples/dot build

fractal:
	$(MAKE) -C ./examples/fractal build

examples-clean:
	$(MAKE) -C ./examples/dot clean
	$(MAKE) -C ./examples/fractal clean

examples-distclean:
	$(MAKE) -C ./examples/dot distclean
	$(MAKE) -C ./examples/fractal distclean

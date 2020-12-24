OBJ = $(BUILD_DIRECTORY)/examples/landscape-generator/landscape-generator.o \
	  $(BUILD_DIRECTORY)/examples/landscape-generator/CommonEvents.o \
	  $(BUILD_DIRECTORY)/examples/landscape-generator/Player.o \
	  $(BUILD_DIRECTORY)/examples/landscape-generator/Chunk.o \
	  $(BUILD_DIRECTORY)/examples/landscape-generator/World.o \
	  $(BUILD_DIRECTORY)/examples/landscape-generator/CommonConsole.o

build: landscape-generator-dirs $(BIN_DIRECTORY)/landscape-generator

$(BIN_DIRECTORY)/landscape-generator: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoXML -lPocoFoundation -lexpat -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/landscape-generator.o: landscape-generator.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/World.o: World.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/Player.o: Player.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/Chunk.o: Chunk.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/CommonConsole.o: ../common/CommonConsole.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/landscape-generator/CommonEvents.o: ../common/CommonEvents.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

landscape-generator-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/landscape-generator

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/landscape-generator/*.o
	@rm -f $(BIN_DIRECTORY)/landscape-generator

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/landscape-generator

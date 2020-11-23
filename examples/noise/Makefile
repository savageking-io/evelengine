OBJ = $(BUILD_DIRECTORY)/examples/noise/noise.o \
	  $(BUILD_DIRECTORY)/examples/noise/NoiseConsole.o \
	  $(BUILD_DIRECTORY)/examples/noise/CommonEvents.o \
	  $(BUILD_DIRECTORY)/examples/noise/CommonConsole.o

build: noise-dirs $(BIN_DIRECTORY)/noise

$(BIN_DIRECTORY)/noise: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoFoundation -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/noise/noise.o: noise.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/noise/NoiseConsole.o: NoiseConsole.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/examples/noise/CommonConsole.o: ../common/CommonConsole.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/noise/CommonEvents.o: ../common/CommonEvents.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

noise-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/noise

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/noise/*.o
	@rm -f $(BIN_DIRECTORY)/noise

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/noise

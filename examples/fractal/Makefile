OBJ = $(BUILD_DIRECTORY)/examples/fractal/fractal.o

build: fractal-dirs $(BIN_DIRECTORY)/fractal

$(BIN_DIRECTORY)/fractal: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/fractal/fractal.o: fractal.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

fractal-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/fractal

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/fractal/*.o
	@rm -f $(BIN_DIRECTORY)/fractal

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/fractal

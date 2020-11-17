OBJ = $(BUILD_DIRECTORY)/examples/render/render.o \
	  $(BUILD_DIRECTORY)/examples/render/CommonEvents.o \
	  $(BUILD_DIRECTORY)/examples/render/CommonConsole.o

build: render-dirs $(BIN_DIRECTORY)/render

$(BIN_DIRECTORY)/render: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoFoundation -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/render/render.o: render.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/render/CommonConsole.o: ../common/CommonConsole.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/render/CommonEvents.o: ../common/CommonEvents.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

render-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/render

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/render/*.o
	@rm -f $(BIN_DIRECTORY)/render

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/render

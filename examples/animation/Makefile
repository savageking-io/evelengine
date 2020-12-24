OBJ = $(BUILD_DIRECTORY)/examples/animation/animation.o \
	  $(BUILD_DIRECTORY)/examples/animation/CommonEvents.o \
	  $(BUILD_DIRECTORY)/examples/animation/CommonConsole.o

build: animation-dirs $(BIN_DIRECTORY)/animation

$(BIN_DIRECTORY)/animation: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoXML -lPocoFoundation -lexpat -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/animation/animation.o: animation.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/animation/CommonConsole.o: ../common/CommonConsole.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/animation/CommonEvents.o: ../common/CommonEvents.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

animation-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/animation

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/animation/*.o
	@rm -f $(BIN_DIRECTORY)/animation

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/animation

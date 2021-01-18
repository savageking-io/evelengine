OBJ = $(BUILD_DIRECTORY)/examples/towerdefense/towerdefense.o \
	  $(BUILD_DIRECTORY)/examples/towerdefense/CommonEvents.o \
	  $(BUILD_DIRECTORY)/examples/towerdefense/CommonConsole.o

build: towerdefense-dirs $(BIN_DIRECTORY)/towerdefense

$(BIN_DIRECTORY)/towerdefense: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoXML -lPocoFoundation -lexpat -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/towerdefense/towerdefense.o: towerdefense.cpp
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/towerdefense/CommonConsole.o: ../common/CommonConsole.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

$(BUILD_DIRECTORY)/examples/towerdefense/CommonEvents.o: ../common/CommonEvents.cpp 
	$(CXX) $(CXXFLAGS) -I../common -c $< -o $@

towerdefense-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/towerdefense

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/towerdefense/*.o
	@rm -f $(BIN_DIRECTORY)/towerdefense

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/towerdefense

OBJ = $(BUILD_DIRECTORY)/testsuite/AnimationFileAsepriteTest.o \
	$(BUILD_DIRECTORY)/testsuite/TilesetTiledTest.o \
	$(BUILD_DIRECTORY)/testsuite/AnimationFileShoeBoxTest.o \
	$(BUILD_DIRECTORY)/testsuite/StringsUtilTest.o \
	$(BUILD_DIRECTORY)/testsuite/ConfigurationBaseTest.o \
	$(BUILD_DIRECTORY)/testsuite/FileSystemTest.o \
	$(BUILD_DIRECTORY)/testsuite/TestSuite.o 

suite: test-dirs $(BIN_DIRECTORY)/testsuite

$(BIN_DIRECTORY)/testsuite: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -lcppunit -levelengine -ljsoncpp -lspdlog -lfmt -lPocoXML -lPocoFoundation -lexpat -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/testsuite/AnimationFileAsepriteTest.o: AnimationFileAsepriteTest.cpp AnimationFileAsepriteTest.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/TilesetTiledTest.o: TilesetTiledTest.cpp TilesetTiledTest.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/AnimationFileShoeBoxTest.o: AnimationFileShoeBoxTest.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/ConfigurationBaseTest.o: ConfigurationBaseTest.cpp ConfigurationBaseTest.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/StringsUtilTest.o: StringsUtilTest.cpp StringsUtilTest.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/FileSystemTest.o: FileSystemTest.cpp FileSystemTest.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/TestSuite.o: TestSuite.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/testsuite

clean: 
	@rm -f $(BUILD_DIRECTORY)/testsuite/*.o 
	@rm -f $(BIN_DIRECTORY)/testsuite

mrproper: clean
	@rm -rf $(BUILD_DIRECTORY)/testsuite

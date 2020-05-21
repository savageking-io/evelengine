OBJ = $(BUILD_DIRECTORY)/testsuite/AnimationFileJSONTest.o \
	$(BUILD_DIRECTORY)/testsuite/StringsUtilTest.o \
	$(BUILD_DIRECTORY)/testsuite/FileSystemTest.o \
	$(BUILD_DIRECTORY)/testsuite/TestSuite.o 

suite: test-dirs $(BIN_DIRECTORY)/testsuite

$(BIN_DIRECTORY)/testsuite: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -lcppunit -levelengine -ljsoncpp -lspdlog -lfmt $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/testsuite/AnimationFileJSONTest.o: AnimationFileJSONTest.cpp AnimationFileJSONTest.hpp
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

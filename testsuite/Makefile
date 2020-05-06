OBJ = $(BUILD_DIRECTORY)/testsuite/AnimationFileJSONTest.o \
	$(BUILD_DIRECTORY)/testsuite/StringsUtilTest.o \
	$(BUILD_DIRECTORY)/testsuite/FileSystemTest.o \
	$(BUILD_DIRECTORY)/testsuite/TestSuite.o 

suite: test-dirs $(BIN_DIRECTORY)/testsuite

$(BIN_DIRECTORY)/testsuite: $(OBJ)
	$(CC) $(LDFLAGS) -L$(LIB_DIRECTORY) -levelengine -lcppunit $(OBJ) -o $@

$(BUILD_DIRECTORY)/testsuite/AnimationFileJSONTest.o: AnimationFileJSONTest.cpp AnimationFileJSONTest.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/StringsUtilTest.o: StringsUtilTest.cpp StringsUtilTest.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/FileSystemTest.o: FileSystemTest.cpp FileSystemTest.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIRECTORY)/testsuite/TestSuite.o: TestSuite.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

test-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/testsuite

clean: 
	@rm -f $(BUILD_DIRECTORY)/testsuite/*.o 
	@rm -f $(BIN_DIRECTORY)/testsuite

mrproper: clean
	@rm -rf $(BUILD_DIRECTORY)/testsuite

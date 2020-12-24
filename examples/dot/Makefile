OBJ = $(BUILD_DIRECTORY)/examples/dot/dot.o

build: dot-dirs $(BIN_DIRECTORY)/dot

$(BIN_DIRECTORY)/dot: $(OBJ)
	$(CXX) $(OBJ) -L$(LIB_DIRECTORY) -levelengine -ljsoncpp -lspdlog -lfmt -lPocoXML -lPocoFoundation -lexpat -lpthread -lyaml-cpp $(LDFLAGS) -o $@

$(BUILD_DIRECTORY)/examples/dot/dot.o: dot.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dot-dirs:
	@mkdir -p $(BIN_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/examples/dot

clean:
	@rm -f $(BUILD_DIRECTORY)/examples/dot/*.o
	@rm -f $(BIN_DIRECTORY)/dot

distclean: clean
	@rm -rf $(BUILD_DIRECTORY)/examples/dot

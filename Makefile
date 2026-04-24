CXX = g++
CXXFLAGS := -c
OBJ_FILES := main.o os.o vars.o log.o readconf.o configvars.o pluginloader.o prompt.o
SRC_FOLDER = src/main/

libreterminal: $(OBJ_FILES)
	@echo "Linking and building 'libreterminal' binary"
	$(CXX) $(OBJ_FILES) -o libreterminal

lt-plugin: lt-plugin.o
	@echo "Linking and building 'lt-plugin' binary"
	$(CXX) lt-plugin.o -o lt-plugin

main.o: $(SRC_FOLDER)main.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)main.cpp

os.o: $(SRC_FOLDER)os.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)os.cpp

vars.o: $(SRC_FOLDER)vars.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)vars.cpp

log.o: $(SRC_FOLDER)log.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)log.cpp

readconf.o: $(SRC_FOLDER)readconf.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)readconf.cpp

configvars.o: $(SRC_FOLDER)configvars.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)configvars.cpp

lt-plugin.o: $(SRC_FOLDER)plugin_sys/lt-plugin.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)plugin_sys/lt-plugin.cpp

pluginloader.o: $(SRC_FOLDER)plugin_sys/pluginloader.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)plugin_sys/pluginloader.cpp

prompt.o: $(SRC_FOLDER)prompt.cpp
	$(CXX) $(CXXFLAGS) $(SRC_FOLDER)prompt.cpp

clean:
	@echo "Removing object files"
	rm $(OBJ_FILES) lt-plugin.o

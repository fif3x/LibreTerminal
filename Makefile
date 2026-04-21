CXX = g++
CXXFLAGS := -c
OBJ_FILES := main.o os.o vars.o log.o readconf.o configvars.o pluginloader.o

libreterminal: $(OBJ_FILES)
	@echo "Linking and building 'libreterminal' binary"
	$(CXX) $(OBJ_FILES) -o libreterminal

lt-plugin: lt-plugin.o
	@echo "Linking and building 'lt-plugin' binary"
	$(CXX) lt-plugin.o -o lt-plugin

main.o: src/main/main.cpp
	$(CXX) $(CXXFLAGS) src/main/main.cpp

os.o: src/main/os.cpp
	$(CXX) $(CXXFLAGS) src/main/os.cpp

vars.o: src/main/vars.cpp
	$(CXX) $(CXXFLAGS) src/main/vars.cpp

log.o: src/main/log.cpp
	$(CXX) $(CXXFLAGS) src/main/log.cpp

readconf.o: src/main/readconf.cpp
	$(CXX) $(CXXFLAGS) src/main/readconf.cpp

configvars.o: src/main/configvars.cpp
	$(CXX) $(CXXFLAGS) src/main/configvars.cpp

lt-plugin.o: src/main/lt-plugin.cpp
	$(CXX) $(CXXFLAGS) src/main/lt-plugin.cpp

pluginloader.o: src/main/pluginloader.cpp
	$(CXX) $(CXXFLAGS) src/main/pluginloader.cpp

clean:
	@echo "Removing object files"
	rm $(OBJ_FILES) lt-plugin.o

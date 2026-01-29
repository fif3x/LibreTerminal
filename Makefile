CXX = g++

libreterminal: main.o os.o vars.o log.o readconf.o configvars.o
	@echo "Linking and building binary"
	$(CXX) main.o os.o vars.o log.o readconf.o configvars.o -o libreterminal

main.o: src/main/main.cpp
	$(CXX) -c src/main/main.cpp

os.o: src/main/os.cpp
	$(CXX) -c src/main/os.cpp

vars.o: src/main/vars.cpp
	$(CXX) -c src/main/vars.cpp

log.o: src/main/log.cpp
	$(CXX) -c src/main/log.cpp

readconf.o: src/main/readconf.cpp
	$(CXX) -c src/main/readconf.cpp

configvars.o: src/main/configvars.cpp
	$(CXX) -c src/main/configvars.cpp

clean:
	@echo "Removing object files"
	rm main.o os.o vars.o log.o readconf.o configvars.o

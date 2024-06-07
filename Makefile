all:
	g++ -std=c++20 ./src/main.cpp -I./include/ -lsysstats -o main.sh -Wall

libTest:
	g++ -std=c++20 ./src/main.cpp ./src/CPUStats.cpp ./src/RAMStats.cpp -I./include -o main.sh -Wall

libBuild:
	g++ -std=c++20 ./src/CPUStats.cpp -I./include -fPIC -g -c -o ./obj/CPUstats.o -Wall
	g++ -std=c++20 ./src/RAMStats.cpp -I./include -fPIC -g -c -o ./obj/RAMstats.o -Wall
	g++ -std=c++20 -shared -Wl,-soname,libsysstats.so -o ./lib/libsysstats.so ./obj/CPUstats.o ./obj/RAMstats.o

debBuild:
	dpkg-deb --root-owner-group --build sysstatsapp
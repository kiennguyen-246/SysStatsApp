sysstatsapp.sh: ./src/main.cpp /usr/lib/libsysstats.so
	g++ -std=c++20 ./src/main.cpp -I./include/ -lsysstats -o sysstatsapp.sh -Wall

test:
	g++ -std=c++20 ./src/main.cpp ./src/CPUStats.cpp ./src/RAMStats.cpp -I./include/ -o sysstatsapp.sh -Wall
	./sysstatsapp.sh 3

./lib/libsysstats.so: ./src/CPUStats.cpp ./src/RAMStats.cpp
	g++ -std=c++20 ./src/CPUStats.cpp -I./include -fPIC -g -c -o ./obj/CPUstats.o -Wall
	g++ -std=c++20 ./src/RAMStats.cpp -I./include -fPIC -g -c -o ./obj/RAMstats.o -Wall
	g++ -std=c++20 -shared -Wl,-soname,libsysstats.so -o ./lib/libsysstats.so ./obj/CPUstats.o ./obj/RAMstats.o

sysstatsapp.deb: ./sysstatsapp.sh ./lib/libsysstats.so ./sysstatsapp/DEBIAN/control ./sysstatsapp/etc/systemd/system/sysstatsapp.service 
	cp ./sysstatsapp.sh ./sysstatsapp/bin/
	cp ./lib/libsysstats.so ./sysstatsapp/usr/lib
	dpkg-deb --root-owner-group --build sysstatsapp

clean:
	rm sysstatsapp.sh
	rm ./obj/CPUstats.o
	rm ./obj/RAMstats.o
	rm ./lib/libsysstats.so
	rm sysstatsapp.deb
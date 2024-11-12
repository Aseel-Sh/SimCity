simulation: main.o Config.o Region.o Commercial.o Residential.o Industrial.o
	g++ main.o Config.o Region.o Commercial.o Residential.o Industrial.o -o simulation

main.o: main.cpp
	g++ -c main.cpp

Config.o: Config.cpp Config.h
	g++ -c Config.cpp

Region.o: Region.cpp Region.h
	g++ -c Region.cpp

Commercial.o: Commercial.cpp Commercial.h
	g++ -c Commercial.cpp

Residential.o: Residential.cpp Residential.h
	g++ -c Residential.cpp

Industrial.o: Industrial.cpp Industrial.h
	g++ -c Industrial.cpp

clean:
	rm *.o simulation

run:
	./simulation
all: hola

GXXFLAGS = -Wall -g

hola: hola.cpp arbolB.h
	g++ $(CXXFLAGS) -o hola hola.cpp -lncurses

clean:
	rm hola
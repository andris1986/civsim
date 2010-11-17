all: main.o
	g++ main.o -o civsim -lglut

main.o:
	g++ -c main.cpp -o main.o


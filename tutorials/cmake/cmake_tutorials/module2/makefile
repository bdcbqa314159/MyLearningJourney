calculator: main.o addition.o soustraction.o printer.o
	g++ -std=c++17 main.o addition.o soustraction.o printer.o -o calculator

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

addition.o: addition.cpp
	g++ -std=c++17 -c addition.cpp

soustraction.o: soustraction.cpp
	g++ -std=c++17 -c soustraction.cpp

printer.o: printer.cpp
	g++ -std=c++17 -c printer.cpp

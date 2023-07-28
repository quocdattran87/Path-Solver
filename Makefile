.default: all

all: solver

clean:
	rm -rf solver *.o *.out

solver: Node.o NodeList.o PathSolver.o main.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
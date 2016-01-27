all: main
main: main.cpp sudoku.cpp
	g++ main.cpp sudoku.cpp -o main
main.cpp: sudoku.h
	g++ -c main.cpp
sudoku.cpp: sudoku.h
	g++ -c sudoku.cpp
clean:
	rm -f *.o main

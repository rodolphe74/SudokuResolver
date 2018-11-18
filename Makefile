CC=g++
CFLAGS=-Wall -Werror -O2
CLIBS=-lcurses -lform

all: SudokuResolver

SudokuResolver: main.o SudokuResolver.o SudokuGrid.o
	$(CC) $(CFLAGS) -o SudokuResolver main.o SudokuResolver.o SudokuGrid.o $(CLIBS)

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp $(CLIBS)

SudokuResolver.o: SudokuResolver.cpp 
	$(CC) $(CFLAGS) -c SudokuResolver.cpp $(CLIBS)

SudokuGrid.o: SudokuGrid.cpp 
	$(CC) $(CFLAGS) -c SudokuGrid.cpp $(CLIBS)


.PHONY: clean

clean:
	-rm -f *.o SudokuResolver

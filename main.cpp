#include "SudokuGrid.h"
#include "SudokuResolver.h"


int main() {

	SudokuGrid sudokuGrid;
	sudokuGrid.screenLoop();
	int *grid = sudokuGrid.getGrid();


	SudokuResolver sudokuResolver;
	initscr();
	sudokuResolver.resolve(grid);
	SudokuGrid::printGrid(sudokuResolver.lastResolvedGrid);
	getch();
	endwin();

	return 0;
}

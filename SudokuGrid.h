/*
 * SudokuGrid.h
 *
 *  Created on: 17 nov. 2018
 *      Author: rodolphe
 */

#ifndef SUDOKUGRID_H_
#define SUDOKUGRID_H_

#include <curses.h>
#include <form.h>

#define UNASSIGNED -1
#define NOT_FOUND -1

class SudokuGrid {
private:
	int grid[9*9];
	FIELD *field[9*9 + 1];
	FORM  *form;
	int ch;

public:
	SudokuGrid();
	virtual ~SudokuGrid();

	void screenLoop();

	void print();

	static void printGrid(int *aGrid);

	int* getGrid() {
		return grid;
	}
};

#endif /* SUDOKUGRID_H_ */

/*
 * SudokuReolver.h
 *
 *  Created on: 17 nov. 2018
 *      Author: rodolphe
 */

#ifndef SUDOKURESOLVER_H_
#define SUDOKURESOLVER_H_

#define UNASSIGNED -1
#define NOT_FOUND -1

class SudokuResolver {

private:
	int findUnassignedCell(int *grid);
	int usedInARow(int *grid, int row, int val);
	int usedInACol(int *grid, int col, int val);
	int usedInABox(int *grid, int col, int row, int val);
	int isSafe(int *grid, int col, int row, int val);

public:
	int lastResolvedGrid[81];
	SudokuResolver();
	virtual ~SudokuResolver();
	int *resolve(int *grid);
};

#endif /* SUDOKURESOLVER_H_ */

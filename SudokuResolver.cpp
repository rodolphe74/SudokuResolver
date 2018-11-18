/*
 * SudokuReolver.cpp
 *
 *  Created on: 17 nov. 2018
 *      Author: rodolphe
 */

#include "SudokuResolver.h"
#include "SudokuGrid.h"

#include <form.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

SudokuResolver::SudokuResolver() {
}

SudokuResolver::~SudokuResolver() {
}

int SudokuResolver::findUnassignedCell(int *grid) {
	for (int i = 0; i < 81; i++) {
		if (grid[i] == UNASSIGNED) {
			return i;
		}
	}
	return NOT_FOUND;
}

int SudokuResolver::isSafe(int *grid, int col, int row, int val) {
	return (!usedInARow(grid, row, val) && !usedInACol(grid, col, val)
			&& !usedInABox(grid, col - col % 3, row - row % 3, val)
			&& grid[col + row * 9] == UNASSIGNED);
}

int *SudokuResolver::resolve(int *grid) {
	int pos = UNASSIGNED;

	// stop recursion condition (no more position available)
	if ((pos = findUnassignedCell(grid)) == NOT_FOUND) {
		return NULL;
	}

	for (int val = 1; val <= 9; val++) {
		int row = pos / 9;
		int col = pos % 9;
		if (isSafe(grid, col, row, val)) {
			// Try with this number on this position
			grid[pos] = val;

			SudokuGrid::printGrid(grid);
 			// getch();
			usleep(1000);

			// No more position available, done !
			if (resolve(grid) == NULL) {
				memcpy(lastResolvedGrid, grid, 81 * sizeof(int));
				return NULL;
			}
			// that was not a good idea, go back and try something else
			grid[pos] = UNASSIGNED;
		}
	}
	return grid;
}

int SudokuResolver::usedInARow(int *grid, int row, int val) {
	for (int c = 0; c < 9; c++) {
		int r = row * 9;
		if (grid[r + c] == val) {
			return 1;
		}
	}
	return 0;
}

int SudokuResolver::usedInACol(int *grid, int col, int val) {
	for (int r = 0; r < 9; r++) {
		int row = r * 9;
		if (grid[row + col] == val) {
			return 1;
		}
	}
	return 0;
}

int SudokuResolver::usedInABox(int *grid, int col, int row, int val) {
	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			int cc = c + col;
			int rr = row * 9 + r * 9;
			if (grid[rr + cc] == val) {
				return 1;
			}
		}
	}
	return 0;
}



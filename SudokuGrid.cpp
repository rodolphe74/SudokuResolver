/*
 * SudokuGrid.cpp
 *
 *  Created on: 17 nov. 2018
 *      Author: rodolphe
 */

#include "SudokuGrid.h"
#include <curses.h>
#include <form.h>

SudokuGrid::SudokuGrid() {
	form = NULL;
	ch = 0;
	for (int i = 0; i < 81; i++) {
		grid[i] = -1;
	}
}

void SudokuGrid::screenLoop() {

	/* Initialize curses */
	initscr();	// init curses
	cbreak();	// disable input buffering
	noecho();	// suppress the automatic echoing of typed characters
	keypad(stdscr, TRUE);// capture special keystrokes like Backspace, Delete and the four arrow keys by getch()

	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int col = i % 9;
		field[i] = new_field(1, 1, row, col * 2, 0, 0);

		set_field_back(field[i], A_UNDERLINE); /* Print a line for the option 	*/
		field_opts_off(field[i], O_AUTOSKIP); /* Don't go to next field when this Field is filled up */
		set_field_type(field[i], TYPE_INTEGER, 0, 0, 9);
	}
	field[81] = NULL;

	form = new_form(field);
	post_form(form);
	refresh();

	while ((ch = getch()) != KEY_F(1)) {
		switch (ch) {
		case KEY_RIGHT:
			/* Go to next field */
			form_driver(form, REQ_RIGHT_FIELD);
			break;
		case KEY_LEFT:
			/* Go to previous field */
			form_driver(form, REQ_LEFT_FIELD);
			break;
		case KEY_UP:
			/* Go to next field */
			form_driver(form, REQ_UP_FIELD);
			break;
		case KEY_DOWN:
			/* Go to previous field */
			form_driver(form, REQ_DOWN_FIELD);
			break;
		default:
			/* If this is a normal character, it gets printed */
			form_driver(form, ch);
			form_driver(form, REQ_NEXT_FIELD);
			break;
		}
	}

	// Feed grid with field values
	for (int i = 0; i < 81; i++) {
		// printf("%s", (char *) field_buffer(field[i], 0));
		// sscanf((char *) field_buffer(field[i], 0), "%i", &grid[i]);
		char *str = new char[2];
		str = field_buffer(field[i], 0);
		int val = -1;
		sscanf(str, "%i", &val);
		grid[i] = val;
		delete[] str;
	}

	/* Un post form and free the memory */
	unpost_form(form);
	free_form(form);

	for (int i = 0; i < 81; i++) {
		free_field(field[i]);
	}

	endwin();
}

void SudokuGrid::print() {

	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int col = i % 9;
		if (grid[i] != UNASSIGNED) {
			mvprintw(row, col * 2, "%i", grid[i]);
		} else {
			mvprintw(row, col * 2, "%s", "_");
		}
	}

	refresh();
}

void SudokuGrid::printGrid(int *aGrid) {
	for (int i = 0; i < 81; i++) {
		int row = i / 9;
		int col = i % 9;
		if (aGrid[i] != UNASSIGNED) {
			mvprintw(row, col * 2, "%i", aGrid[i]);
		} else {
			mvprintw(row, col * 2, "%s", "_");
		}
	}

	refresh();
}

SudokuGrid::~SudokuGrid() {
}


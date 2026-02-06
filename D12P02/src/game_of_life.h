#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <ncurses.h>
#include <stdio.h>

#define ROWS 25
#define COLS 80
#define MIN_DELAY 40
#define MAX_DELAY 1000
#define DELAY_STEP 40

void fill_default(int field[ROWS][COLS]);
int read_mode_from_user(void);
void change_stream(int mode);
void restore_stdin(void);
void read_field(int field[ROWS][COLS]);
int wrap_row(int row);
int wrap_col(int col);
int neighbors_count(int field[ROWS][COLS], int row, int col);
int next_cell(int alive, int neighbors);
void evolve(int field[ROWS][COLS], int next[ROWS][COLS]);
void copy_field(int from[ROWS][COLS], int to[ROWS][COLS]);
void draw_field(int field[ROWS][COLS], int delay_ms, int mode, int generation);
void process_input(int *delay_ms, int *running);
void run_game(int field[ROWS][COLS], int mode);

#endif // GAME_OF_LIFE_H

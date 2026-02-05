#include <ncurses.h>
#include <stdio.h>

#define ROWS 25
#define COLS 80
#define MIN_DELAY 40
#define MAX_DELAY 1000
#define DELAY_STEP 40

void fill_default(int field[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      field[i][j] = 0;
    }
  }
}

int read_field(int field[ROWS][COLS]) {
  int ok = 1;
  fill_default(field);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int value = 0;
      if (scanf("%d", &value) == 1) {
        field[i][j] = value != 0;
      }
    }
  }
  return ok;
}

int wrap_row(int row) {
  int res = row;
  if (res < 0) {
    res += ROWS;
  }
  if (res >= ROWS) {
    res -= ROWS;
  }
  return res;
}

int wrap_col(int col) {
  int res = col;
  if (res < 0) {
    res += COLS;
  }
  if (res >= COLS) {
    res -= COLS;
  }
  return res;
}

int neighbors_count(int field[ROWS][COLS], int row, int col) {
  int count = 0;
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if (!(dr == 0 && dc == 0)) {
        int nr = wrap_row(row + dr);
        int nc = wrap_col(col + dc);
        count += field[nr][nc];
      }
    }
  }
  return count;
}

int next_cell(int alive, int neighbors) {
  int next = 0;
  if (alive) {
    next = neighbors == 2 || neighbors == 3;
  } else {
    next = neighbors == 3;
  }
  return next;
}

void evolve(int field[ROWS][COLS], int next[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int near = neighbors_count(field, i, j);
      next[i][j] = next_cell(field[i][j], near);
    }
  }
}

void copy_field(int from[ROWS][COLS], int to[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      to[i][j] = from[i][j];
    }
  }
}

void draw_field(int field[ROWS][COLS], int delay_ms) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      mvaddch(i, j, field[i][j] ? '#' : '.');
    }
  }
  mvprintw(ROWS, 0, "A/Z speed  SPACE exit  delay:%dms", delay_ms);
  refresh();
}

void process_key(int key, int *delay_ms, int *running) {
  if (key == 'A' || key == 'a') {
    if (*delay_ms > MIN_DELAY) {
      *delay_ms -= DELAY_STEP;
    }
  } else if (key == 'Z' || key == 'z') {
    if (*delay_ms < MAX_DELAY) {
      *delay_ms += DELAY_STEP;
    }
  } else if (key == ' ') {
    *running = 0;
  }
}

void run_game(int field[ROWS][COLS]) {
  int next[ROWS][COLS];
  int running = 1;
  int delay_ms = 200;
  timeout(delay_ms);
  while (running) {
    draw_field(field, delay_ms);
    process_key(getch(), &delay_ms, &running);
    timeout(delay_ms);
    evolve(field, next);
    copy_field(next, field);
  }
}

int main(void) {
  int field[ROWS][COLS];
  int ok = read_field(field);
  if (ok) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    run_game(field);
    endwin();
  }
  return 0;
}

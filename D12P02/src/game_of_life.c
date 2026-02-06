#include "game_of_life.h"

void fill_default(int field[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      field[i][j] = 0;
    }
  }
}

int read_mode_from_user(void) {
  int mode = 0;
  int valid = 0;
  while (!valid) {
    printf("Введите корректное число от 1 до 5:\n");
    if (scanf("%d", &mode) == 1) {
      if (mode >= 1 && mode <= 5) {
        valid = 1;
      } else {
        printf("Ошибка! Введите корректное число от 1 до 5.\n");
      }
    } else {
      printf("Ошибка! Введите корректное число от 1 до 5.\n");
    }
    int ch = getchar();
    while (ch != '\n' && ch != EOF) {
      ch = getchar();
    }
  }
  return mode;
}

void change_stream(int mode) {
  if (mode == 1) {
    freopen("./presets/1.txt", "r", stdin);
  } else if (mode == 2) {
    freopen("./presets/2.txt", "r", stdin);
  } else if (mode == 3) {
    freopen("./presets/3.txt", "r", stdin);
  } else if (mode == 4) {
    freopen("./presets/4.txt", "r", stdin);
  } else if (mode == 5) {
    freopen("./presets/5.txt", "r", stdin);
  }
}

void restore_stdin(void) { freopen("/dev/tty", "r", stdin); }

void read_field(int field[ROWS][COLS]) {
  fill_default(field);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int value = 0;
      if (scanf("%d", &value) == 1) {
        field[i][j] = value != 0;
      }
    }
  }
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

void draw_field(int field[ROWS][COLS], int delay_ms, int mode, int generation) {
  clear();
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      mvaddch(i, j, field[i][j] ? '#' : ' ');
    }
  }
  mvprintw(ROWS, 0, "Speed: A/Z | Exit: Space | Mode:%d Gen:%d Delay:%dms",
           mode, generation, delay_ms);
  refresh();
}

void process_input(int *delay_ms, int *running) {
  int ch = getch();
  if (ch == 'A' || ch == 'a') {
    if (*delay_ms > MIN_DELAY) {
      *delay_ms -= DELAY_STEP;
    }
  } else if (ch == 'Z' || ch == 'z') {
    if (*delay_ms < MAX_DELAY) {
      *delay_ms += DELAY_STEP;
    }
  } else if (ch == ' ') {
    *running = 0;
  }
}

void run_game(int field[ROWS][COLS], int mode) {
  int next[ROWS][COLS];
  int running = 1;
  int delay_ms = 200;
  int generation = 0;
  while (running) {
    draw_field(field, delay_ms, mode, generation);
    timeout(delay_ms);
    process_input(&delay_ms, &running);
    evolve(field, next);
    copy_field(next, field);
    generation++;
  }
}

int main(void) {
  int field[ROWS][COLS];
  int mode = read_mode_from_user();
  change_stream(mode);
  read_field(field);
  restore_stdin();
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(0);
  run_game(field, mode);
  endwin();
  return 0;
}

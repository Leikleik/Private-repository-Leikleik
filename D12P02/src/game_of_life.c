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

int parse_mode(const char *arg) {
  int mode = 0;
  if (arg != NULL) {
    if (arg[0] >= '1' && arg[0] <= '6' && arg[1] == '\0') {
      mode = arg[0] - '0';
    }
  }
  return mode;
}

const char *preset_path(int mode) {
  const char *path = NULL;
  if (mode == 2) {
    path = "./presets/cow.txt";
  } else if (mode == 3) {
    path = "./presets/gun_gosper.txt";
  } else if (mode == 4) {
    path = "./presets/gun_simple.txt";
  } else if (mode == 5) {
    path = "./presets/agar.txt";
  } else if (mode == 6) {
    path = "./presets/ship_new.txt";
  }
  return path;
}

const char *preset_fallback_path(int mode) {
  const char *path = NULL;
  if (mode == 2) {
    path = "./D12P02/src/presets/cow.txt";
  } else if (mode == 3) {
    path = "./D12P02/src/presets/gun_gosper.txt";
  } else if (mode == 4) {
    path = "./D12P02/src/presets/gun_simple.txt";
  } else if (mode == 5) {
    path = "./D12P02/src/presets/agar.txt";
  } else if (mode == 6) {
    path = "./D12P02/src/presets/ship_new.txt";
  }
  return path;
}

void read_field_stream(FILE *stream, int field[ROWS][COLS]) {
  fill_default(field);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int value = 0;
      if (fscanf(stream, "%d", &value) == 1) {
        field[i][j] = value != 0;
      }
    }
  }
}

void set_demo_glider(int field[ROWS][COLS]) {
  int center_row = ROWS / 2;
  int center_col = COLS / 2;
  fill_default(field);
  field[center_row][center_col + 1] = 1;
  field[center_row + 1][center_col + 2] = 1;
  field[center_row + 2][center_col] = 1;
  field[center_row + 2][center_col + 1] = 1;
  field[center_row + 2][center_col + 2] = 1;
}

void load_preset(int mode, int field[ROWS][COLS]) {
  const char *path = preset_path(mode);
  const char *fallback_path = preset_fallback_path(mode);
  FILE *file = NULL;
  if (path != NULL) {
    file = fopen(path, "r");
  }
  if (file == NULL && fallback_path != NULL) {
    file = fopen(fallback_path, "r");
  }
  if (file != NULL) {
    read_field_stream(file, field);
    fclose(file);
  } else {
    set_demo_glider(field);
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
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      mvaddch(i, j, field[i][j] ? '#' : '.');
    }
  }
  mvprintw(ROWS, 0, "A/Z speed  SPACE exit  mode:%d  gen:%d  delay:%dms", mode,
           generation, delay_ms);
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

void run_game(int field[ROWS][COLS], int mode) {
  int next[ROWS][COLS];
  int running = 1;
  int delay_ms = 200;
  int generation = 0;
  timeout(delay_ms);
  while (running) {
    draw_field(field, delay_ms, mode, generation);
    process_key(getch(), &delay_ms, &running);
    timeout(delay_ms);
    evolve(field, next);
    copy_field(next, field);
    generation++;
  }
}

int main(int argc, char **argv) {
  int field[ROWS][COLS];
  int mode = 3;
  if (argc > 1) {
    mode = parse_mode(argv[1]);
  }
  if (mode == 1) {
    read_field_stream(stdin, field);
  } else {
    if (mode < 2 || mode > 6) {
      mode = 2;
    }
    load_preset(mode, field);
  }
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  run_game(field, mode);
  endwin();
  return 0;
}

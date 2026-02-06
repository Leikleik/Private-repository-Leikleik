#include <ncurses.h>
#include <stdio.h>

#define ROWS 25
#define COLS 80

void initialize_field(int field[ROWS][COLS]);
void print_field(int field[ROWS][COLS]);
int count_neighbors(int field[ROWS][COLS], int row, int col);
void calculate_next_generation(int current[ROWS][COLS], int next[ROWS][COLS]);
char get_user_input(void);
void print_menu(void);
int read_mode_from_user(void);
void change_stream(int mode);
void restore_stdin(void);

int main(void) {
  int field[ROWS][COLS];
  int next_gen[ROWS][COLS];
  int mode = read_mode_from_user();
  int running = 1;
  change_stream(mode);
  initialize_field(field);
  restore_stdin();
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  while (running) {
    clear();
    print_menu();
    print_field(field);
    char cmd = get_user_input();
    if (cmd == 'n') {
      calculate_next_generation(field, next_gen);
    } else if (cmd == 'q') {
      running = 0;
    } else {
      mvprintw(ROWS + 1, 0, "Неверная команда. Используй n или q.");
    }
  }
  endwin();
  return 0;
}

void initialize_field(int field[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int value = 0;
      if (scanf("%d", &value) == 1) {
        field[i][j] = value != 0;
      } else {
        field[i][j] = 0;
      }
    }
  }
}

void print_field(int field[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      mvaddch(i, j, field[i][j] ? '#' : '.');
    }
  }
  refresh();
}

int count_neighbors(int field[ROWS][COLS], int row, int col) {
  int count = 0;
  for (int dr = -1; dr <= 1; dr++) {
    for (int dc = -1; dc <= 1; dc++) {
      if (!(dr == 0 && dc == 0)) {
        int r = (row + dr + ROWS) % ROWS;
        int c = (col + dc + COLS) % COLS;
        count += field[r][c];
      }
    }
  }
  return count;
}

void calculate_next_generation(int current[ROWS][COLS], int next[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int neighbors = count_neighbors(current, i, j);
      if (current[i][j] == 1) {
        next[i][j] = neighbors == 2 || neighbors == 3;
      } else {
        next[i][j] = neighbors == 3;
      }
    }
  }
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      current[i][j] = next[i][j];
    }
  }
}

char get_user_input(void) {
  int ch = getch();
  flushinp();
  return (char)ch;
}

void print_menu(void) {
  mvprintw(ROWS, 0, "Следующее поколение [n] | Выход [q]");
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

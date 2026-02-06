#include <ncurses.h>
#include <stdio.h>

#define ROWS 25
#define COLS 80
#define MIN_DELAY 40
#define MAX_DELAY 1000
#define DELAY_STEP 40

void initialize_field(int field[ROWS][COLS]);
void print_menu(void);
void print_field(int field[ROWS][COLS]);
int count_neighbors(int field[ROWS][COLS], int row, int col);
void calculate_next_generation(int current[ROWS][COLS], int next[ROWS][COLS]);
char get_user_input(void);
int read_mode_from_user(void);
void process_input(char key, int *delay_ms, int *running);

int main(void) {
  int field[ROWS][COLS];
  int next_gen[ROWS][COLS];
  int delay_ms = 200;
  int running = 1;
  int mode = read_mode_from_user();
  const char *path = NULL;
  FILE *preset_file = NULL;
  switch (mode) {
  case 1:
    path = "./presets/1.txt";
    break;
  case 2:
    path = "./presets/2.txt";
    break;
  case 3:
    path = "./presets/3.txt";
    break;
  case 4:
    path = "./presets/4.txt";
    break;
  case 5:
    path = "./presets/5.txt";
    break;
  default:
    printf("Неверный режим!\n");
    running = 0;
    break;
  }
  if (running) {
    preset_file = fopen(path, "r");
    if (preset_file != NULL) {
      fclose(preset_file);
      freopen(path, "r", stdin);
      initialize_field(field);
      freopen("/dev/tty", "r", stdin);
      initscr();
      noecho();
      cbreak();
      curs_set(0);
      keypad(stdscr, TRUE);
      while (running) {
        clear();
        print_menu();
        print_field(field);
        timeout(delay_ms);
        process_input(get_user_input(), &delay_ms, &running);
        calculate_next_generation(field, next_gen);
      }
      endwin();
    } else {
      printf("Ошибка открытия файла пресета!\n");
    }
  }
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

void print_menu(void) {
  mvprintw(ROWS, 0, "A/Z speed | SPACE exit | Delay: up/down | Next gen auto");
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
  char result = 0;
  if (ch != ERR) {
    result = (char)ch;
  }
  return result;
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

void process_input(char key, int *delay_ms, int *running) {
  switch (key) {
  case 'A':
  case 'a':
    if (*delay_ms > MIN_DELAY) {
      *delay_ms -= DELAY_STEP;
    }
    break;
  case 'Z':
  case 'z':
    if (*delay_ms < MAX_DELAY) {
      *delay_ms += DELAY_STEP;
    }
    break;
  case ' ':
    *running = 0;
    break;
  default:
    break;
  }
}

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define PRESETS 6
#define MIN_DELAY_US 30000
#define MAX_DELAY_US 500000
#define STEP_DELAY_US 20000

int torus_index(int value, int limit) {
    int result = value;
    if (result < 0) {
        result = limit - 1;
    } else if (result >= limit) {
        result = 0;
    }
    return result;
}

void clear_field(int field[HEIGHT][WIDTH]) {
    int row = 0;
    while (row < HEIGHT) {
        int col = 0;
        while (col < WIDTH) {
            field[row][col] = 0;
            col++;
        }
        row++;
    }
}

void set_cell(int field[HEIGHT][WIDTH], int row, int col) {
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        field[row][col] = 1;
    }
}

void place_glider(int field[HEIGHT][WIDTH], int top, int left) {
    set_cell(field, top + 0, left + 1);
    set_cell(field, top + 1, left + 2);
    set_cell(field, top + 2, left + 0);
    set_cell(field, top + 2, left + 1);
    set_cell(field, top + 2, left + 2);
}

void place_blinker(int field[HEIGHT][WIDTH], int top, int left) {
    set_cell(field, top, left);
    set_cell(field, top, left + 1);
    set_cell(field, top, left + 2);
}

void place_block(int field[HEIGHT][WIDTH], int top, int left) {
    set_cell(field, top, left);
    set_cell(field, top, left + 1);
    set_cell(field, top + 1, left);
    set_cell(field, top + 1, left + 1);
}

void fill_preset_1(int field[HEIGHT][WIDTH]) {
    int i = 0;
    clear_field(field);
    while (i < 8) {
        place_glider(field, 2 + i * 2, 3 + i * 5);
        i++;
    }
}

void fill_preset_2(int field[HEIGHT][WIDTH]) {
    int i = 0;
    clear_field(field);
    while (i < WIDTH - 4) {
        place_blinker(field, HEIGHT / 2, i);
        i += 6;
    }
}

void fill_preset_3(int field[HEIGHT][WIDTH]) {
    int row = 1;
    clear_field(field);
    while (row < HEIGHT - 2) {
        int col = 1;
        while (col < WIDTH - 2) {
            place_block(field, row, col);
            col += 6;
        }
        row += 4;
    }
}

void fill_preset_4(int field[HEIGHT][WIDTH]) {
    int i = 0;
    clear_field(field);
    while (i < WIDTH && i < HEIGHT) {
        set_cell(field, i, i * 3 % WIDTH);
        set_cell(field, i, (WIDTH - 1 - i * 2 + WIDTH) % WIDTH);
        i++;
    }
}

void fill_preset_5(int field[HEIGHT][WIDTH]) {
    int row = 0;
    clear_field(field);
    while (row < HEIGHT) {
        int col = 0;
        while (col < WIDTH) {
            if ((row + col) % 7 == 0) {
                set_cell(field, row, col);
            }
            col++;
        }
        row++;
    }
}

void fill_preset_6(int field[HEIGHT][WIDTH]) {
    int row = 0;
    clear_field(field);
    while (row < HEIGHT) {
        int col = 0;
        while (col < WIDTH) {
            if ((row * col) % 11 == 0 && (row + col) % 3 == 0) {
                set_cell(field, row, col);
            }
            col++;
        }
        row++;
    }
}

void init_preset(int field[HEIGHT][WIDTH], int preset) {
    if (preset == 1) {
        fill_preset_1(field);
    } else if (preset == 2) {
        fill_preset_2(field);
    } else if (preset == 3) {
        fill_preset_3(field);
    } else if (preset == 4) {
        fill_preset_4(field);
    } else if (preset == 5) {
        fill_preset_5(field);
    } else {
        fill_preset_6(field);
    }
}

int count_neighbors_torus(const int field[HEIGHT][WIDTH], int row, int col) {
    int sum = 0;
    int dr = -1;
    while (dr <= 1) {
        int dc = -1;
        while (dc <= 1) {
            if (!(dr == 0 && dc == 0)) {
                int rr = torus_index(row + dr, HEIGHT);
                int cc = torus_index(col + dc, WIDTH);
                sum += field[rr][cc];
            }
            dc++;
        }
        dr++;
    }
    return sum;
}

int build_next_generation(const int current[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    int status = 1;
    int marker = count_neighbors_torus(current, 0, 0);
    (void)marker;
    (void)next;
    return status;
}

void draw_field(const int field[HEIGHT][WIDTH], int delay_us, int algorithm_ready) {
    int row = 0;
    erase();
    while (row < HEIGHT) {
        int col = 0;
        while (col < WIDTH) {
            mvaddch(row, col, field[row][col] ? 'O' : '.');
            col++;
        }
        row++;
    }
    mvprintw(HEIGHT, 0, "A/Z speed | SPACE quit | delay=%dus", delay_us);
    if (!algorithm_ready) {
        mvprintw(HEIGHT + 1, 0, "Основной алгоритм не реализован: добавьте правила в build_next_generation().");
    }
    refresh();
}

void swap_fields(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]) {
    int row = 0;
    while (row < HEIGHT) {
        int col = 0;
        while (col < WIDTH) {
            int t = a[row][col];
            a[row][col] = b[row][col];
            b[row][col] = t;
            col++;
        }
        row++;
    }
}

void update_delay(int key, int *delay_us) {
    if (key == 'a' || key == 'A') {
        *delay_us -= STEP_DELAY_US;
        if (*delay_us < MIN_DELAY_US) {
            *delay_us = MIN_DELAY_US;
        }
    } else if (key == 'z' || key == 'Z') {
        *delay_us += STEP_DELAY_US;
        if (*delay_us > MAX_DELAY_US) {
            *delay_us = MAX_DELAY_US;
        }
    }
}

void run_loop(int field[HEIGHT][WIDTH], int delay_us) {
    int next[HEIGHT][WIDTH];
    int running = 1;
    int ready = 0;
    clear_field(next);
    while (running) {
        int key = getch();
        if (key == ' ') {
            running = 0;
        } else {
            update_delay(key, &delay_us);
            ready = (build_next_generation(field, next) == 0);
            if (ready) {
                swap_fields(field, next);
            }
            draw_field(field, delay_us, ready);
            usleep((useconds_t)delay_us);
        }
    }
}

int read_menu_choice(void) {
    int choice = 0;
    printf("Выберите карту (1-6):\n");
    printf("1) Диагональ глайдеров\n");
    printf("2) Полоса осцилляторов\n");
    printf("3) Сетка стабильных блоков\n");
    printf("4) Крест-диагонали\n");
    printf("5) Редкая сетка\n");
    printf("6) Псевдослучайный узор\n");
    printf("> ");
    if (scanf("%d", &choice) != 1) {
        choice = 1;
    }
    if (choice < 1 || choice > PRESETS) {
        choice = 1;
    }
    return choice;
}

void start_ncurses(void) {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

void finish_ncurses(void) {
    nodelay(stdscr, FALSE);
    curs_set(1);
    endwin();
}

int main(void) {
    int field[HEIGHT][WIDTH];
    int choice = read_menu_choice();
    int delay_us = 140000;
    init_preset(field, choice);
    start_ncurses();
    draw_field(field, delay_us, 0);
    run_loop(field, delay_us);
    finish_ncurses();
    return 0;
}

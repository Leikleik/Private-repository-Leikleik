#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void sort_doors(struct door* doors, int count);
void close_doors(struct door* doors, int count);
void print_doors(const struct door* doors, int count);
void swap_doors(struct door* first, struct door* second);

int main(void)
{
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    sort_doors(doors, DOORS_COUNT);
    close_doors(doors, DOORS_COUNT);
    print_doors(doors, DOORS_COUNT);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors)
{
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void swap_doors(struct door* first, struct door* second)
{
    struct door temp = *first;
    *first = *second;
    *second = temp;
}

void sort_doors(struct door* doors, int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (doors[j].id > doors[j + 1].id) {
                swap_doors(&doors[j], &doors[j + 1]);
            }
        }
    }
}

void close_doors(struct door* doors, int count)
{
    for (int i = 0; i < count; i++) {
        doors[i].status = 0;
    }
}

void print_doors(const struct door* doors, int count)
{
    for (int i = 0; i < count; i++) {
        printf("%d, %d\n", doors[i].id, doors[i].status);
    }
}

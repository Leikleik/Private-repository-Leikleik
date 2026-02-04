#include "data_io.h"

#include <stdio.h>

int input(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &data[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%.2f", data[i]);
    }
}

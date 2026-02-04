#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main() {
    double *data = NULL;
    int n = 0;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("ERROR");
        return 0;
    }

    data = (double *)malloc(sizeof(double) * n);
    if (!data) {
        printf("ERROR");
        return 0;
    }

    input(data, n);

    if (normalization(data, n)) {
        output(data, n);
    } else {
        printf("ERROR");
    }

    free(data);
    return 0;
}

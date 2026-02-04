#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data = NULL;
    int n = 0;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("NO");
        return 0;
    }

    data = (double *)malloc(sizeof(double) * n);
    if (!data) {
        printf("NO");
        return 0;
    }

    if (!input(data, n)) {
        printf("NO");
    } else if (make_decision(data, n)) {
        printf("YES");
    } else {
        printf("NO");
    }

    free(data);
    return 0;
}

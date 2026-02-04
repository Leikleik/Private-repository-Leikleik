#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

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

    printf("LOAD DATA...\n");
    if (!input(data, n)) {
        printf("ERROR");
        free(data);
        return 0;
    }

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    if (normalization(data, n)) {
        output(data, n);
    } else {
        printf("ERROR");
        free(data);
        return 0;
    }

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n)) {
        printf("YES");
    } else {
        printf("NO");
    }

    free(data);
    return 0;
}

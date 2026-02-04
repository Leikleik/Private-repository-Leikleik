#include "data_stat.h"

double max(double *data, int n) {
    double max_value = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_value) {
            max_value = data[i];
        }
    }
    return max_value;
}

double min(double *data, int n) {
    double min_value = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < min_value) {
            min_value = data[i];
        }
    }
    return min_value;
}

double mean(double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

double variance(double *data, int n) {
    double avg = mean(data, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = data[i] - avg;
        sum += diff * diff;
    }
    return sum / n;
}

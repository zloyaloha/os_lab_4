#include "gcf-pi.h"

float Pi(int k) {
    float res = 1;
    for (int n = 1; n < k + 1; ++n) {
        res *= ((4 * pow(n, 2)) / (4 * pow(n, 2) - 1));
    }
    return 2 * res;
}

int GCF(int A, int B) {
    int del = 1;
    int max;
    while (del < A && del < B) {
        if (A % del == 0 && B % del == 0) {
            max = del;
        }
        ++del;
    }
    return max;
}
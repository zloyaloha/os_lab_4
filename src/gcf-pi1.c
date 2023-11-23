#include "gcf-pi.h"

float Pi(int k) {
    float res = -1;
    for (int n = 0; n < k + 1; ++n) {
        res = res + (-pow(-1, n) / (2 * n - 1));
    }
    return 4 * res;
}

int GCF(int A, int B) {
    while (A != 0 && B != 0) {
        if (A > B) {
            A = A % B;
        } else {
            B = B % A;
        }
    }
    return A + B;
}
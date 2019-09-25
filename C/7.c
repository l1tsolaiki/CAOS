#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t sum;
    if (__builtin_add_overflow(v1, v2, &sum)) {
        if (v1 > 0 && v2 > 0) {
            return (uint32_t) -1 >> 1;
        }
        if (v1 < 0 && v2 < 0) {
            return ~((uint32_t) -1 >> 1);
        }
    }
    return sum;
}

int main (int argc, char const *argv[]) {
    int32_t a, b, sum;
	scanf("%d%d", &a, &b);
    sum = satsum(a, b);
	printf("%d\n", sum);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    uint32_t sum = v1 + v2;
    if (sum >= v1 && sum >= v2) {
        return sum;
    } else {
        sum = v1 + ~v1;
        return sum;
    }
}

int main (int argc, char const *argv[]) {
    uint32_t a, b, sum;
	scanf("%u%u", &a, &b);
    sum = satsum(a, b);
	printf("%u\n", sum);
    return 0;
}

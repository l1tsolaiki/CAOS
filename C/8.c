#include <stdio.h>
#include <stdlib.h>

int bitcount(int value) {
    int count = 0;
    while (value) {
        ++count;
        value = value & (value - 1);
    }
    return count;
}

int main(int argc, char const *argv[]) {
    int value;
    scanf("%d", &value);
    printf("%d\n", bitcount(value));
    return 0;
}
